
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cuda.h>
//#include <cuda_runtime.h>
#include <math.h>
#include "atom_class.h"
#include "bond_class.h"

void read_prmtop(int test, char *prmtopFileName, atom *atoms, bond *bonds) {

	char line[80];
	char const *FlagSearch="%%FLAG";
	char const *search = " ";
	char *flag;
	char *token;
	FILE *prmFile = fopen(prmtopFileName, "r");

	printf("in subroutine: %s\n", prmtopFileName);
	printf("in subroutine: %d\n", test);
	if ( prmFile != NULL) {
		while (fgets(line, sizeof line, prmFile) != NULL) {
			printf("%s",line);
			//token = strtok(line, '%FLAG');
			if (strncmp(line,FlagSearch,5)==0) {
				token = strtok(line, search);
				flag = strtok(NULL, search);
				printf("FLAG: %s\n", flag);			
			}
		}
		fclose( prmFile );
	}

}




