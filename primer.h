#ifndef PRIMER_H
#define PRIMER_H

#include <vector>
#include <string>

using namespace std;

/* The primer class stores the primer, the frequencies of each base at each position,
and an array of bases and positions (e.g. a1, t6, etc.).
In contraction.cpp, this array of bases is in order from least to most frequent
*/

class Primer{
	int seq_length;
	std::vector<char> *sequence; // a table of the possible bases at each position
	float **frequency_table;   // a table of frequency of bases @ e. pos. in order [actg]
	float *frequencies;
	std::string *bases;
	
	public:
		Primer (int);
		Primer (float*, string*, int);
		void print_sequence();
		void print_iupac_sequence();
		int get_degeneracy();
};

#endif