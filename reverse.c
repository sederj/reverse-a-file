/*
 * Main function which will read in a string form a text file,
 * reverse the string, and print it out to a different text file.
 * The first additional parameter specifies the input file.
 * The second additional parameter specifies theoutput file.
 *
 * @author Joseph Seder
 */

#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	// check that there are 3 arguments
	if (argc != 3) {
		fprintf(stderr, "Wrong number of inputs");
		return -1;
	}

	// read in file to buffer
	char* buffer;
	int size_input = read_file(argv[1], &buffer); 

	// write string in reverse order to same buffer
	char temp;
	for (int i = 0; i < size_input / 2; i++) {
		temp = buffer[i];
		buffer[i] = buffer[size_input - 1 - i];
		buffer[size_input - 1 - i] = temp;
	}	

	// write new reversed string to output file
	int size_output = write_file(argv[2], buffer, size_input);

	// ensure the files are equivalent sizes
	if (size_input != size_output) {
		fprintf(stderr, "input and output files do not match size!");
	}
	
	// free the memory locations of the buffer
	free(buffer);

	return 0;
}
