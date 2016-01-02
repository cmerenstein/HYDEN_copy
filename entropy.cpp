#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <new>
#include "entropy.h"

using namespace std;

distribution_t get_distribution(string *alignment, int k, int num_seqs){
	/* gets an array for each base with the frequency at each position.
	k is the size of sequences being aligned*/
	distribution_t dist;
	dist.table = new float*[4];

	for (int j = 0; j<4; j++){
		dist.table[j] = new float[k];
		for (int i = 0; i< k; i++){
			dist.table[j][i] = 0;
		}
	}	
	int i; // through each letter of sequence
	int j; // through each sequence
	for (j = 0; j < num_seqs; j++){
		string seq = alignment[j];
		for (i = 0; i < k; i++){
			switch (seq[i]){ // TODO replace with map
				case 'a':
					dist.table[0][i]++;
					break;
				case 'c':
					dist.table[1][i]++;
					break;
				case 'g':
					dist.table[2][i]++;
					break;
				case 't':
					dist.table[3][i]++;
					break;
			}
		}
	}
	float n = float(num_seqs);
	for (j = 0; j < 4; j++){
		for (i = 0; i < k; i++){ // change count to percent
			dist.table[j][i] = float(dist.table[j][i])/n;
		}
	}
	return dist;
}

float calc_entropy(const distribution_t& dist, int k){
	float entropy = 0;
	for (int j = 0; j< 4; j++){ 
		for (int i= 0; i < k; i++){
			float freq = dist.table[j][i];
			if (freq > 0.01){
				entropy += (freq * log2(freq));
			}
		}
	}
	// if (entropy > 0){
		// for (int j = 0; j<4;j++){
			// for (int i = 0; i<k;i++){
				//cout << dist.table[j][i] <<endl;
				// printf(" %f ", dist.table[j][i]);
			// }
			// cout << endl;
		// }
	// }
	
	return -(entropy);
}