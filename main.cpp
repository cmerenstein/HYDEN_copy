#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "halign.h"
#include "contraction.h"

// TODO: getopt() for cmd parameters

int main(int argc, char* argv[]){
	
	const char *file_name = "cbbl_unique.fasta";
	alignment_t *alignments;
	alignments = halign(file_name);
	
	int i;
	for (i = 0; i<100;i++){
		Primer p = sort_alignment(alignments[i]);
		p.print_iupac_sequence();
	}
}