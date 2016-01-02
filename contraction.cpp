#include "contraction.h"

using namespace std;
const int k = 20; // Must stay same as k in halign.cpp TODO: move both to main

/*
The contraction step creates a degenerate primer by starting with a fully degenerate
primer (e.g. NNNN...) and removing the least used at each step.
This is accomplished by making an ordered list of bases and positions and removing from the front
*/

Primer sort_alignment(alignment_t align){
/* This function is used to actually generate the Primer object from an alignment.
Because this is the contraction algorithm, it puts in all possible bases at each position
(i.e. if at least 1 sequence in the alignment has that base at that position).
*/
	map<float, vector<string> > freq_pos; // frequency and position.
	float frequencies[k*4];
	
	distribution_t d;
	d = align.dist;
	
	int q;
	for (int j = 0; j<4; j++){
		for (int i = 0; i<k;i++){
			frequencies[q] = align.dist.table[j][i];
			q++;
		}
	}
	//cout << "boom goes the dynamite" << endl;
	map<int, string> base_order = {{0, "a"}, {1,"c"},{2,"g"},{3,"t"}};
	
	for (int j = 0; j<4;j++){
		for (int i = 0; i<k; i++){
			string position = to_string(i); // move these out of the loop?
			float frequency;
			string base_position = base_order[j] + position;
			frequency = align.dist.table[j][i];
			freq_pos[frequency].push_back(base_position);			
		}
	}
	
	sort(begin(frequencies), end(frequencies));
	string inorder_base_positions[k*4];
	
	for (int i = 0; i < k*4; i++){
		inorder_base_positions[i] = freq_pos[frequencies[i]].front();
		freq_pos[frequencies[i]].erase(freq_pos[frequencies[i]].begin());
	}
	
	// for (i = 0; i < k*4; i++){
		// cout << inorder_base_positions[i] << ": " << frequencies[i] << endl;
	// }
	
	return Primer(frequencies, inorder_base_positions, k*4);
}

Primer contract(Primer p){
	
}