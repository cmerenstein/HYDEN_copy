#include "contraction.h"

using namespace std;
const int k = 20; // Must stay same as k in halign.cpp TODO: move both to main

/*
The contraction step creates a degenerate primer by starting with a fully degenerate
primer (e.g. NNNN...) and removing the least used at each step.
This is accomplished by making an ordered list of bases and positions and removing from the front
*/

void sort_alignment(alignment_t align){
	map<float, vector<string> > freq_pos; // frequency and position.
	float frequencies[k*4];
	
	distribution_t d;
	d = align.dist;
	
	int i;
	for (i = 0; i<k;i++){
		frequencies[(i*4)] = align.dist.a[i];
		frequencies[(i*4)+1] = align.dist.t[i];
		frequencies[(i*4)+2] = align.dist.c[i];
		frequencies[(i*4)+3] = align.dist.g[i];
	}
	cout << "boom goes the dynamite" << endl;
	for (i = 0; i<k; i++){
		string position = to_string(i);
		float frequency;
		
		// because distribution_t has 4 different arrays, need to add each letter manually for now
		// TODO make this way cleaner (2d array for distribution_t)
		string base_position = "a" + position;
		frequency = align.dist.a[i];
		try {	
			freq_pos[frequency].push_back(base_position);
		}
		catch (int e) {
			cout << "error " << e << endl;
			// freq_pos[align.dist.a[i]];
			// freq_pos[align.dist.a[i]].push_back(base_position);
		}
		cout << " i = " << i << "  " << frequency << " ";
		int size = freq_pos[frequency].size();
		cout << freq_pos[frequency].size() << ": ";
		int print_ct;
		for (print_ct = 0; print_ct < size; print_ct++){
			cout << freq_pos[frequency][print_ct] << ", ";
		}
		cout << endl;
		// base_position = "t" + position;
		// try {
			// freq_pos[align.dist.t[i]].push_back(base_position);
		// }
		// catch (int e) {
			// freq_pos[align.dist.t[i]] = new vector<string>;
			// freq_pos[align.dist.t[i]].push_back(base_position);		
		// }
		
		// base_position = "c" + position;
		// try }
			// freq_pos[align.dist.c[i]].push_back(base_position);
		// }
		// catch (int e) {
			// freq_pos[align.dist.c[i]] = new vector<string>;
			// freq_pos[align.dist.c[i]].push_back(base_position);			
		// }
		
		// base_position = "g" + position;
		// try {
			// freq_pos[align.dist.g[i]].push_back(base_position);
		// }
		// catch (int e) {
			// freq_pos[align.dist.g[i]] = new vector<string>;
			// freq_pos[align.dist.g[i]].push_back(base_position);
		// }
}
	
	// for (i = 0; i < k*4; i++){
		// cout << frequencies[i] << endl;
	// }
	
	// cout << "sorted:" << endl;
	
	// sort(begin(frequencies), end(frequencies));
	// for (i = 0; i < k*4; i++){
		// cout << frequencies[i] << endl;
	// }
	
}

