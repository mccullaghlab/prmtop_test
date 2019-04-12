
/* test code */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "atom_class.h"
#include "bond_class.h"
#include "config_class.h"
#include "read_prmtop.h"

void read_cfg_file(char*, config& configs);
void read_prmtop(char*); //, atom * , bond *);

int main (int argc, char* argv[]) {

	char *paramFileName;
	atom atoms;
	bond bonds;
	config configs;

	read_cfg_file(argv[1],configs);
	printf("prmtop file name: %s\n", configs.prmtopFileName);
	read_prmtop(configs.prmtopFileName); //, atoms, bonds);

}

void read_cfg_file(char* cfgFile, config& configs) {

	char *token;
	char const *search = "=";
	char line[128]; // maximum number of character per line set to 128
	char *paramFileName;
	FILE *inFile = fopen(cfgFile,"r");
	printf("in subroutine: %s\n", cfgFile);
	if ( inFile != NULL) {
		while (fgets(line, sizeof line, inFile) != NULL) {
			token = strtok(line, search);
			if (strcmp(token,"prmtop")==0) {
				configs.prmtopFileName = strtok(NULL, search);
			}
		}
		fclose( inFile );
	}
}

void read_prmtop(char* prmtopFileName) {

	char line[80];
	char const *FlagSearch = "\%FLAG";
	char const *search = " ";
	char *flag;
	char *token;
	FILE *prmFile = fopen(prmtopFileName, "r");

	printf("in subroutine: %s\n", prmtopFileName);
	printf("Flag: %s\n", FlagSearch);
	if ( prmFile != NULL) {
		while (fgets(line, sizeof line, prmFile) != NULL) {
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




