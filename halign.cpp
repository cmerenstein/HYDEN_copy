#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "halign.h"

using namespace std;


const int k = 20; // length of the primers we're looking for
const int num_alignments = 100;

void halign(const char* fasta_file){
	
	ifstream seqs_in(fasta_file);
	
	vector<string> sequences;
	string line;
	alignment_t best_alignments[num_alignments]; // This is definitely not the best data structure for this, dunno if it will effect much
	initialize_best_alignments(best_alignments);
	
	
	while(getline(seqs_in, line)){
		if (line[0] != '>'){
			sequences.push_back(line);
		}
	}
	
	int num_seqs = sequences.size();
	
	int a, b, c, d;
	for (a = 0; a < sequences.size(); a++){
		printf("\r%.0f%% aligned.", (float(a)/float(sequences.size()))*100);
		string s_a = sequences[a];
		for ( b = 0; (b + k) < s_a.size(); b++){
			string kmer = s_a.substr(b, k);
			alignment_t align;
			align = get_alignment(kmer, sequences, a);
			save_alignment(best_alignments, align);
			if (align.entropy > 30.0){ //if this one didn't align well, then the next few probably won't either
				b += 4; 
			}
		}
	}
	printf("\n");
	int i;
	for (i = 0; i < num_alignments; i++){
		print_alignment(best_alignments[i]);
	}
}

alignment_t get_alignment(const string& probe, vector<string>& sequences, const int a){
/* for a given kmer, or probe, return the alignment that fits best.
First only tries with every 5th sequence, then if the average mismatches of that alignment is low enough,
it extends for all sequences and returns the alignment.*/

	float threashold = 0.5; // arbitrary. Will be replaced with the xth best alignment so far.
	vector<string> initial_alignment;
	alignment_t best_alignment;
	float sum_mismatches = 0;

	int c;
	float n;
	for ( c = 0; c < sequences.size(); c+= 5){
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
			if (c%5 == 0 && c != a){
				int index_initial = int(float(c)/5.0);
				best_alignment.kmers.push_back(initial_alignment[index_initial]);
			}
			if (c != a){ // don't compare sequence to itself
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
		int mismatches = k;
		
		int e;
		for (e = 0; e < k; e++){
		/* looking at a few bp at a time and storing comparisons in an array for reuse might improve speed?*/
			if (sub_target[e] == probe[e]){				
				mismatches--;
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