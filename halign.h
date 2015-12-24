#ifndef HALIGN_H
#define HALIGN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "entropy.h"


struct alignment_t {
	std::vector<std::string> kmers;
	distribution_t dist;
	double entropy;
};

alignment_t* halign(const char* fasta_file);
std::string align_kmer(const std::string& target, const std::string& probe, const int& k, int& min_mismatches);
alignment_t get_alignment(const std::string& target, std::vector<std::string>& sequences, const int a);
void initialize_best_alignments(alignment_t* best_alignment);
void save_alignment(alignment_t* best_alignments, alignment_t new_alignment);
void print_alignment(const alignment_t& alignment);

#endif