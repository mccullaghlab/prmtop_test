
/* test code */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "atom_class.h"
#include "bond_class.h"
#include "config_class.h"
#include "stringlib.h"
//#include "read_prmtop.h"

void read_cfg_file(char*, config& );
void read_prmtop(config , char*); //, atom * , bond *);

#define MAXCHAR 250
#define MAXLEN 80
int main (int argc, char* argv[]) {

	char *paramFileName;
	atom atoms;
	bond bonds;
	config configs;

	read_cfg_file(argv[1],configs);
	printf("prmtop file name: %s\n", configs.prmtopFileName);
	printf("prmtop file name: %s\n", configs.prmtopFileName);
	read_prmtop(configs, configs.prmtopFileName); //, atoms, bonds);
	printf("prmtop file name: %s\n", configs.prmtopFileName);

}

void read_cfg_file(char* cfgFile, config& configs) {

	char *token;
	char *firstToken;
	char temp[MAXLEN];
	char const *search = "=";
	char const *comment = "#";
	char line[MAXCHAR]; // maximum number of character per line set to 128
	char *paramFileName;
	FILE *inFile = fopen(cfgFile,"r");
	printf("in subroutine: %s\n", cfgFile);
	if ( inFile != NULL) {
		while (fgets(line, MAXCHAR, inFile) != NULL) {
			firstToken = strtok(line,comment);
			token = strtok(firstToken, search);
			if (strcmp(token,"prmtop")==0) {
				printf("prmtop\n");
				strncpy(temp,strtok(NULL, search),MAXLEN);
				configs.prmtopFileName = trim(temp);
				printf("%s\n",configs.prmtopFileName);
			}
		}
		fclose( inFile );
	}
}

void read_prmtop(config configs, char* prmtopFileName) {

	char line[MAXCHAR];
	char const *FlagSearch = "\%FLAG";
	char const *search = " ";
	char *flag;
	char *token;
	FILE *prmFile = fopen(prmtopFileName, "r");

	printf("in subroutine: %s\n", prmtopFileName);
	printf("in subroutine: %s\n", configs.prmtopFileName);
	printf("Flag: %s\n", FlagSearch);
	if ( prmFile != NULL) {
		while (fgets(line, MAXCHAR, prmFile) != NULL) {
			printf("%s,%d\n", line, strncmp(line,FlagSearch,5));
			if (strncmp(line,FlagSearch,5)==0) {
				token = strtok(line, search);
				flag = strtok(NULL, search);
				printf("FLAG: %s\n", flag);			
			}
		}
		fclose( prmFile );
	}

}




