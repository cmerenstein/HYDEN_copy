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
	dist.a = new float[k];
	dist.t = new float[k];
	dist.c = new float[k];
	dist.g = new float[k];
	
	int i; // through each letter of sequence
	int j; // through each sequence
	for (j = 0; j < num_seqs; j++){
		string seq = alignment[j];
		for (i = 0; i < k; i++){
			switch (seq[i]){
				case 'a':
					dist.a[i]++;
					break;
				case 't':
					dist.t[i]++;
					break;
				case 'c':
					dist.c[i]++;
					break;
				case 'g':
					dist.g[i]++;
					break;
			}
		}
	}
	for (i = 0; i < k; i++){ // change count to percent
		float n = float(num_seqs);
		dist.a[i] = float(dist.a[i])/n;
		dist.t[i] = float(dist.t[i])/n;
		dist.c[i] = float(dist.c[i])/n;
		dist.g[i] = float(dist.g[i])/n;
	}
	return dist;
}

float calc_entropy(const distribution_t& dist, int k){
	int i;
	float entropy = 0;
	for (i= 0; i < k; i++){
		if (dist.a[i] > 0.01){
			entropy += (dist.a[i] * log2(dist.a[i]));
		}
		if (dist.t[i] > 0.01){
			entropy += (dist.t[i] * log2(dist.t[i]));
		}
		if (dist.c[i] > 0.01){
			entropy += (dist.c[i] * log2(dist.c[i]));
		}
		if (dist.g[i] > 0.01){
			entropy += (dist.g[i] * log2(dist.g[i]));
		}
	}
	return -(entropy);
}