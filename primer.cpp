#include "primer.h"
#include <iostream>
#include <algorithm>

Primer::Primer (int k) {
	frequencies = new float[k*4];
	bases = new string[k*4];
}

Primer::Primer(float *freq, string *inorder_base_positions, int size){
	// 
	
	seq_length = size/4;
	frequencies = freq;
	bases = inorder_base_positions;
	sequence = new vector<char>[seq_length];
	
	int i;
	for (i = 0; i < size; i++){ // this part is to build the sequence
		if (frequencies[i] != 0) {
			char base = bases[i][0]; // char gets put into the sequence
			int pos = stoi(bases[i].substr(1), nullptr);
			sequence[pos].push_back(base);
		}
	}
}

void Primer::print_sequence(){
	int i;
	for (i = 0; i< seq_length; i++){
		vector<char> position = sequence[i];
		int j;
		cout << '[';
		for (j = 0; j < position.size(); j++){
			printf("%c,", position[j]);
		}
		cout << "], ";
	}
	cout << endl;
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