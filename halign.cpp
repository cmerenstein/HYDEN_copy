#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
#include "halign.h"

using namespace std;


const int k = 20; // length of the primers we're looking for. TODO: move to main.cpp
const int num_alignments = 100;

alignment_t* halign(const char* fasta_file){
/* A heuristic that returns an alignment_t of kmers from each sequence that minimizes
the total entropy value. It simply checks each kmer against every other for each sequence.
2 shortcuts makes this faster: 1) it starts by checking only every 5th sequence, then only
tries the rest if it's a possibly good match
2) if a kmer doesn't lead to a good alignment, the next few kmers in that sequence get skipped
and are not used to seed a new alignment, since they share a lot of sequence with the one
that was bad.
*/	
	ifstream seqs_in(fasta_file);
	
	vector<string> sequences;
	string line;
	static alignment_t best_alignments[num_alignments]; // This is definitely not the best data structure for this, dunno if it will effect much
	initialize_best_alignments(best_alignments);
	
	bool not_first = false; // set to false after the first line
	string sequence;
	
	while(getline(seqs_in, line)){
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		if (line[0] != '>'){
			sequence = sequence + line;
		}
		else {		// in fasta format the > line always comes first
			if (not_first){
				sequences.push_back(sequence);
			}
			else {
				not_first = true;
			}
			
			string sequence = "";
		}
	}
	sequences.push_back(sequence); // put in the last one
	
	int stride;			// used for skipping through sequences before trying to align all
	if (sequences.size() < 12){ // play with these numbers more
		if (sequences.size() < 5){
			stride = 1;
		}
		else {
			stride = 2;
		}
	}
	else {
		stride = 5;
	}
	
	
	int num_seqs = sequences.size();
	printf("%d sequences.\n", num_seqs);
	
	int a, b, c, d; // a loops through sequences, b thru sequence a, c thru all sequences, d thru sequence c
	for (a = 0; a < sequences.size(); a++){
		printf("\r%.0f%% aligned.", (float(a)/float(sequences.size()))*100);
		string s_a = sequences[a];
		for ( b = 0; (b + k) < s_a.size(); b++){
			// if (b%100 == 0) {
				// printf("on base %d of sequence %d\r", b, a);
			// }
			string kmer = s_a.substr(b, k);
			alignment_t align;
			align = get_alignment(kmer, sequences, a, stride);
			save_alignment(best_alignments, align);
			if (align.entropy > 30.0){ //if this one didn't align well, then the next few probably won't either
				b += 4; 
			}
		}
	}
	printf("\n");
	// int i;
	// for (i = 0; i < num_alignments; i++){
		// print_alignment(best_alignments[i]);
	// }
	return best_alignments;
}

alignment_t get_alignment(const string& probe, vector<string>& sequences, const int a, int& stride){
/* for a given kmer, or probe, return the alignment that fits best.
First only tries with every 5th sequence, then if the average mismatches of that alignment is low enough,
it extends for all sequences and returns the alignment.*/

	float threashold = 0.5; // arbitrary. Will be replaced with the xth best alignment so far.
	vector<string> initial_alignment;
	alignment_t best_alignment;
	float sum_mismatches = 0;
	
	int c;
	float n;
	for ( c = 0; c < sequences.size(); c+= stride){
		if (c != a){ // don't compare sequence to itself
			int min_mismatches = k;
			string best_match = align_kmer(sequences[c], probe, k, min_mismatches);
			initial_alignment.push_back(best_match);
			//printf("the best match has %d mismatches\n", min_mismatches);
			sum_mismatches =+ min_mismatches;
			n++;
		}
		else {
			initial_alignment.push_back(probe);
		}
		
	}
	// printf("the average mismatches is %f\n", (sum_mismatches/n));
	if (sum_mismatches/n < threashold){
		for ( c = 0; c < sequences.size(); c++){
			if (c%stride == 0 && c != a){ // don't redo the ones we've seen
				int index_initial = int(float(c)/float(stride)); // where it is in the initial alignment
				best_alignment.kmers.push_back(initial_alignment[index_initial]);
			}
			else if (c != a){ // don't compare sequence to itself
				int min_mismatches = k;
				string best_match = align_kmer(sequences[c], probe, k, min_mismatches);
				best_alignment.kmers.push_back(best_match);
				//printf("the best match has %d mismatches\n", min_mismatches);
				sum_mismatches =+ min_mismatches;
			}
		}
		best_alignment.dist = get_distribution(best_alignment.kmers, k);
		best_alignment.entropy = calc_entropy(best_alignment.dist, k);
		// cout << best_alignment.entropy << endl;
	}
	else {
		// printf("\n");
		best_alignment.entropy = 999; // don't bother to calculate entropy for bad ones
	}
	
    return best_alignment;
}

string align_kmer(const string& target, const string& probe, const int& k, int& min_mismatches) {
/* Just counts mismatches, and finds the closest matching ungapped alignment in the target.
Can be improved using popcnt instruction, or even better with SSE3*/

	string best;
	bool first_time = true;
	
	int d;
	for (d = 0; (d + k) < target.size(); d++){
		string sub_target = target.substr(d, k);
		int mismatches = 0;
		
		int e;
		for (e = 0; e < k; e++){
		/* looking at a few bp at a time and storing comparisons in an array for reuse might improve speed?*/
			if (sub_target[e] != probe[e]){				
				mismatches++;
				if (mismatches > min_mismatches){ // this makes it much faster
					break;
				}
			}
		}

		if (mismatches < min_mismatches){
			best = sub_target;
			min_mismatches = mismatches;
		}
	}
	return best;
}

void initialize_best_alignments(alignment_t* best_alignments){
/* in order to clear out whatever is there in memory so things can properly be saved in it later */

	int i;
	for (i = 0; i < num_alignments; i++){
		best_alignments[i].entropy = 999.0;
	}
}

void save_alignment(alignment_t* best_alignments, alignment_t new_alignment){
/* if it has a lower entropy score than the highest that's saved, put it in, and pop off the highest.
Order doesn't matter, so we'll just go through, keep track of the highest, then at the end replace it */

	int highest = 0; // where the highest is
	float highest_entropy = 0; // what the highest entropy score is
	float new_entropy = new_alignment.entropy;
	
	int i;
	for (i = 0; i < num_alignments; i++){ // we have to recalculate where the highest one is every time
		if (best_alignments[i].entropy > highest_entropy){
			highest_entropy = best_alignments[i].entropy;
			highest = i;
		}
	}
	if (new_entropy < highest_entropy && new_entropy > 0){
		best_alignments[highest] = new_alignment;
	}
}

void print_alignment(const alignment_t& alignment){
	int i;
	for (i = 0; i < alignment.kmers.size(); i++){
		cout << alignment.kmers[i] << endl;
	}
	printf("Entropy = %f\n", alignment.entropy);
}