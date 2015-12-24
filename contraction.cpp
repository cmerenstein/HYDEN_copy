#include "contraction.h"
using namespace std;
const int k = 20; // Must stay same as k in halign.cpp TODO: move both to main

/*
The contraction step creates a degenerate primer by starting with a fully degenerate
primer (e.g. NNNN...) and removing the least used at each step.
This is accomplished by making an ordered list of bases and positions and removing from the front
*/

void sort_alignment(alignment_t align){
	vector<vector<string> > freq_pos; // frequency and position.
	float frequencies[k*4];
	
	distribution_t d;
	d = align.dist;
	
	int i;
	for (i = 0; i<k;i++){
		string position = to_string(i);
		string frequency;
		
		// because distribution_t has 4 different arrays, need to add each letter manually for now
		vector<string> a_entry;
		string a_position = "a" + position;
		a_entry.push_back(a_position);
		frequency = to_string(align.dist.a[i]);
		a_entry.push_back(frequency);
		freq_pos.push_back(a_entry);
		cout << a_position << " " << frequency << endl;
		
		vector<string> t_entry;
		string t_position = "t" + position;
		t_entry.push_back(t_position);
		frequency = to_string(align.dist.t[i]);
		t_entry.push_back(frequency);
		freq_pos.push_back(t_entry);
		
		vector<string> c_entry;
		string c_position = "c" + position;
		c_entry.push_back(c_position);
		frequency = to_string(align.dist.c[i]);
		c_entry.push_back(frequency);
		freq_pos.push_back(c_entry);
		
		vector<string> g_entry;
		string g_position = "g" + position;
		g_entry.push_back(g_position);
		frequency = to_string(align.dist.g[i]);
		g_entry.push_back(frequency);
		freq_pos.push_back(g_entry);
		
				
	}
}