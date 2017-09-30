/*
 * This function reads in text from a file into a string
 *
 * @param filename pointer to input file name
 * @param buffer the address of a pointer to first string element
 * @author Joseph Seder
 *
 */
 
#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int read_file( char* filename, char **buffer ) {
	// open file
	FILE *fptr;
	fptr = fopen(filename, "r");

	// check that input file exists
	if (fptr == NULL) {
		fprintf(stderr, "Problem opening file %s \n", filename);
		exit(-1);
	}
	
	// determine the size of the input file to allocate correct memory amount
	struct stat st;
	stat(filename, &st);
	int size = st.st_size;

	// allocate space for the string buffer in memory	
	*buffer = (char*)malloc(size * sizeof(char));

	// check that buffer was created correctly
	if (*buffer == NULL) {
		fprintf(stderr, "Memory not allocated correctly");
		exit(-1);
	}	

	// read the text file into string buffer
	fread(*buffer, size, 1, fptr);

	// close the file pointer
	fclose(fptr);
	
	// return the size of the input file to ensure it matches the output file
	return size;
} 

/*
 * This function writes a string to an output file
 *
 * @param filename pointer to output file name
 * @param buffer a pointer to first string element
 * @param size the size of the string
 * @author Joseph Seder
 */
int write_file( char* filename, char *buffer, int size) {
	// open file 
	FILE *fptr;
	fptr = fopen(filename, "w");

	// check that output file exists	
	if (fptr == NULL) {
		fprintf(stderr, "Error writing to file \n");
		exit(-1);
	}

	// write reversed string to output file
	int writtenSize = fwrite(buffer, size, 1, fptr);

	// ensure the return value does not match the count parameter
	if (writtenSize != 1) {
		fprintf(stderr, "Error writing to file \n");
		exit(-1);
	}
	
	// close the file pointer
	fclose(fptr);

	// return the size of the output file to ensure it matches the 
	// size of the input file
	struct stat st;
	stat(filename, &st);
	int output_size = st.st_size;

	return output_size;
}
 
