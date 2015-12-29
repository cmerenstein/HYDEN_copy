#ifndef PRIMER_H
#define PRIMER_H

#include <vector>
#include <string>

using namespace std;

class Primer{
	int seq_length;
	std::vector<char> *sequence;
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