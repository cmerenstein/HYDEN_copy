#include "primer.h"
#include <iostream>
#include <algorithm>
#include <map>

Primer::Primer (int k) {
	frequencies = new float[k*4];
	bases = new string[k*4];
}

Primer::Primer(float *freq, string *inorder_base_positions, int size){
	// This constructor is what gets used in contraction
	map<char, int> base_order = {{'a',0},{'c',1},{'g',2},{'t',3}}; // for making frequency_table
	seq_length = size/4;
	frequencies = freq;
	bases = inorder_base_positions;
	sequence = new vector<char>[seq_length];
	frequency_table = new float*[seq_length];
	
	int i;
	for (i = 0; i < seq_length; i++){
		int j;
		frequency_table[i] = new float[4];
		for (j = 0; j < 4; j++){
			frequency_table[i][j] = 0; // this just fills it with 0s
		}
	}
	
	for (i = 0; i < size; i++){ // this part is to build the sequence
		if (frequencies[i] != 0) {
			char base = bases[i][0]; // char gets put into the sequence
			int pos = stoi(bases[i].substr(1), nullptr);
			sequence[pos].push_back(base);
			
			int base_num = base_order[base];
			frequency_table[pos][base_num] = frequencies[i]; // puts in the table of frequencies
		}
	}
}

void Primer::print_sequence(){
/* prints the primer, with a [list] of bases at each position */
	int i;
	for (i = 0; i< seq_length; i++){
		vector<char> position = sequence[i]; // vector at each position
		int j;
		cout << '[';
		for (j = 0; j < position.size(); j++){
			printf("%c,", position[j]);
		}
		cout << "], "; // last comma is redundant, but it's not important
	}
	cout << endl;
}

void Primer::print_iupac_sequence(){
/* prints the primer with the ipuac base names */
	map<string, char> iupac = {{"a",'A'},{"c",'C'},{"g",'G'},{"t",'T'},{"ag",'R'},{"ct",'Y'},{"cg",'S'},{"at",'W'},{"gt",'K'},{"ac",'M'},{"cgt",'B'},{"agt",'D'},{"act",'H'},{"acg",'V'},{"acgt", 'N'}};

	string primer_string = "";
	int i;
	for (i = 0; i< seq_length; i++){
		vector<char> v = sequence[i]; // v = vector at position
		int j;
		sort(v.begin(),v.end());
		string temp = "";
		for (j = 0; j<v.size();j++){
			temp = temp + v[j];
		}
		primer_string = primer_string + iupac[temp];
	}
	
	cout << primer_string << endl;
}

int Primer::get_degeneracy(){
	int degeneracy = 1;
	
	int i;
	for (i = 0; i< seq_length; i++){
		vector<char> position = sequence[i];
		degeneracy = degeneracy * position.size();
	}
	return degeneracy;
}

// float Primer::get_coverage(){
	
// }