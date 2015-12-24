#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "halign.h"
#include "contraction.h"

// TODO: add global constants

int main(){
	const char *file_name = "cbbl_unique.fasta";
	alignment_t *alignments;
	alignments = halign(file_name);
	
	int i;
	for (i = 0; i<100;i++){
		sort_alignment(alignments[i]);
	}
}