
/* test code */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "atom_class.h"
#include "bond_class.h"
#include "read_prmtop.h"

char *read_cfg_file(char*);

int main (int argc, char* argv[]) {

	char *paramFileName;
	atom atoms;
	bond bonds;

	paramFileName = read_cfg_file(argv[1]);
	printf("prmtop file name: %s\n", paramFileName);

	read_prmtop(45, paramFileName, &atoms, &bonds);

}

char *read_cfg_file(char* cfgFile) {

	char *token;
	char const *search = "=";
	char line[128]; // maximum number of character per line set to 128
	char *paramFileName;

	FILE *inFile = fopen(cfgFile,"r");

	if ( inFile != NULL) {
		while (fgets(line, sizeof line, inFile) != NULL) {
			token = strtok(line, search);
			if (strcmp(token,"prmtop")==0) {
				paramFileName = strtok(NULL, search);
			}
		}
		fclose( inFile );
	}
	return paramFileName;
}

