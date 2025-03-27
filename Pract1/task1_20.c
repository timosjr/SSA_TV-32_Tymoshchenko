# include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LINE 1024
#define MAX_COLUMNS 100

void print_table(const char *filename, char delimiter){
	FILE *file = fopen(filename, "r");
	if (!file) {S
		perror ("Error opening file");
		return;

	}

	char line[MAX_LINE];
	while (fgets(line, sizeof (line), file)) {
		char *columns [MAX_COLUMNS];
		int col_count = 0;

		char *token = strtok(line, &delimiter) ;
		while (token && col_count < MAX_COLUMNS) {
			columns [col_count++] = token;
			token = strtok (NULL, &delimiter);
		}

		for (int i=0; i<col_count; i++) {
			printf ("%-15s", columns[i]);
		}
		printf ("\n");
	}
	fclose(file);
}

int main(int argc, char *argv[ ]){
	if (argc != 3){
		printf ("Usage: %s <filename> <delimiter>", argv[0]);
		return 1;
	}

	char delimiter = argv[2][0];
	print_table(argv[1], delimiter);
	return 0;
}
