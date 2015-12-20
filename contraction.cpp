#include "halign.h"
#include <vector>
#include <string>


using namespace std;
const int k = 20; // Must stay same as k in halign.cpp TODO: move both to main

/*
The contraction step creates a degenerate primer by starting with a fully degenerate
primer (e.g. NNNN...) and removing the least used at each step.
This is accomplished by making an ordered list of bases and positions and removing from the front
*/

void sort_alignment(alignment_t align){
	vector<vector<string> > freq_pos; // frequency and position.
	float frequency[k*4];
	
	int i;
	for (i = 0; i<k;i++){
		
	}
}