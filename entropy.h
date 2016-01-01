#ifndef ENTROPY_H
#define ENTROPY_H

#include <vector>
#include <string>

struct distribution_t {
/* 	for clarity, use 4 separate pointers rather than a 2d array
	would function better as 2d array, this setup makes contraction program cumbersome
	*/
	
	float** table;
};

distribution_t get_distribution(std::string *alignment, int k, int num_seqs);

float calc_entropy(const distribution_t& dist, int k);

#endif