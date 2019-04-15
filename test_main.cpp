
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
void read_prmtop(char*, atom& , bond&);

#define MAXCHAR 250
#define MAXLEN 80
int main (int argc, char* argv[]) {

	char *paramFileName;
	atom atoms;
	bond bonds;
	config configs;

	read_cfg_file(argv[1],configs);
	read_prmtop(configs.prmtopFileName, atoms, bonds);

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

void read_prmtop(char* prmtopFileName, atom& atoms, bond& bonds) {

	char line[MAXCHAR];
	char const *FlagSearch = "\%FLAG";
	char const *blank = " ";
	char const *metaDataFlag = "POINTERS";
	char const *chargeFlag = "CHARGE";
	char const *massFlag = "MASS";
	char const *atomTypeIndexFlag = "ATOM_TYPE_INDEX";
	char const *nExcludedAtomsFlag = "NUMBER_EXCLUDED_ATOMS";
	char const *nonBondIndexFlag = "NONBONDED_PARM_INDEX";
	char const *bondKFlag = "BOND_FORCE_CONSTANT";
	char const *bondX0Flag = "BOND_EQUIL_VALUE";
	char const *bondnHFlag = "BONDS_WITHOUT_HYDROGEN";
	char const *bondHFlag = "BONDS_INC_HYDROGEN";
	char *flag;
	char *token;
	int i, nLines;
	int bondCount;
	int lineCount;
	int *tempBondArray;
	FILE *prmFile = fopen(prmtopFileName, "r");

	printf("in subroutine: %s\n", prmtopFileName);
	printf("Flag: %s\n", FlagSearch);
	if ( prmFile != NULL) {
		while (fgets(line, MAXCHAR, prmFile) != NULL) {
			if (strncmp(line,FlagSearch,5)==0) {
				token = strtok(line, blank);
				flag = strtok(NULL, blank);
				printf("FLAG: %s\n", flag);
				if (strcmp(flag,metaDataFlag) == 0) {
					// read meta data
					printf("Reading meta data\n");
					/* skip format line */
					fgets(line, MAXCHAR, prmFile);
					/* read meta data section line by line */
					/* line 1: */
					fgets(line, MAXCHAR, prmFile);
					atoms.nAtoms = atoi(strncpy(token,line,8));
					printf("Number of atoms from prmtop file: %d\n", atoms.nAtoms);
					atoms.nAtomTypes = atoi(strncpy(token,line+8,8));
					bonds.nBondHs = atoi(strncpy(token,line+16,8));
					printf("Number of bonds containing hydrogens: %d\n", bonds.nBondHs);
					bonds.nBondnHs = atoi(strncpy(token,line+32,8));
					printf("Number of bonds NOT containing hydrogens: %d\n", bonds.nBondnHs);
					bonds.nBonds = bonds.nBondHs + bonds.nBondnHs;
					/* line 2: */
					fgets(line, MAXCHAR, prmFile);
					bonds.nTypes = atoi(strncpy(token,line+40,8));
					printf("Number of unique bond types: %d\n", bonds.nTypes);
					/* line 3: */
					fgets(line, MAXCHAR, prmFile);
					/* line 4: */
					fgets(line, MAXCHAR, prmFile);

					/* allocate arrays */
					atoms.allocate();
					bonds.allocate();
				} else if (strcmp(flag,bondHFlag) == 0) { 
					/* FORMAT 10I8 */
					nLines = (int) bonds.nBondHs*3 / 10.0 + 1;
					printf("number of lines to read for bonds with hydrogens: %d\n", nLines);
					/* skip format line */
					fgets(line, MAXCHAR, prmFile);
					/* loop over lines */
					bondCount = 0;
					tempBondArray = (int *) malloc(bonds.nBondHs*3*sizeof(int));
					for (i=0;i<nLines;i++) {
						fgets(line, MAXCHAR, prmFile);
						lineCount = 0;
						while (bondCount < bonds.nBondHs*3 && lineCount < 10) {
							tempBondArray[bondCount] = atoi(strncpy(token,line+lineCount*8,8));
							bondCount++;
							lineCount++;
						}
					}
					// parse to bond arrays
					for (i=0;i<bonds.nBondHs;i++) {
						bonds.bondAtoms[i*2] = tempBondArray[i*3]/3;
						bonds.bondAtoms[i*2+1] = tempBondArray[i*3+1]/3;
						bonds.bondKs[i] = bonds.bondKUnique[tempBondArray[i*3+2]-1];
						bonds.bondX0s[i] = bonds.bondX0Unique[tempBondArray[i*3+2]-1];
						printf("Bond %d is between atoms %d and %d with force constant %f and eq value of %f\n", i+1, bonds.bondAtoms[i*2], bonds.bondAtoms[i*2+1],bonds.bondKs[i],bonds.bondX0s[i]);
					}
					free(tempBondArray);
				} else if (strcmp(flag,bondnHFlag) == 0) { 
					/* FORMAT 10I8 */
					nLines = (int) bonds.nBondnHs*3 / 10.0 + 1;
					printf("number of lines to read for bonds without hydrogens: %d\n", nLines);
					/* skip format line */
					fgets(line, MAXCHAR, prmFile);
					/* loop over lines */
					bondCount = 0;
					tempBondArray = (int *) malloc(bonds.nBondnHs*3*sizeof(int));
					for (i=0;i<nLines;i++) {
						fgets(line, MAXCHAR, prmFile);
						lineCount = 0;
						while (bondCount < bonds.nBondnHs*3 && lineCount < 10) {
							tempBondArray[bondCount] = atoi(strncpy(token,line+lineCount*8,8));
							bondCount++;
							lineCount++;
						}
					}
					// parse to bond arrays
					for (i=0;i<bonds.nBondHs;i++) {
						bonds.bondAtoms[(i+bonds.nBondHs)*2] = tempBondArray[i*3]/3;
						bonds.bondAtoms[(i+bonds.nBondHs)*2+1] = tempBondArray[i*3+1]/3;
						bonds.bondKs[(i+bonds.nBondHs)] = bonds.bondKUnique[tempBondArray[i*3+2]-1];
						bonds.bondX0s[(i+bonds.nBondHs)] = bonds.bondX0Unique[tempBondArray[i*3+2]-1];
						printf("Bond %d is between atoms %d and %d with force constant %f and eq value of %f\n", (i+bonds.nBondHs)+1, bonds.bondAtoms[(i+bonds.nBondHs)*2], bonds.bondAtoms[(i+bonds.nBondHs)*2+1],bonds.bondKs[(i+bonds.nBondHs)],bonds.bondX0s[(i+bonds.nBondHs)]);
					}
					free(tempBondArray);
				} else if (strcmp(flag,bondX0Flag) == 0) {
					// read bond k values
					nLines = (int) bonds.nTypes / 5.0 + 1;
					printf("number of lines to read for bond equilibrium value: %d\n", nLines);
					/* skip format line */
					fgets(line, MAXCHAR, prmFile);
					/* loop over lines */
					bondCount = 0;
					for (i=0;i<nLines;i++) {
						fgets(line, MAXCHAR, prmFile);
						lineCount = 0;
						while (bondCount < bonds.nTypes && lineCount < 5) {
							bonds.bondX0Unique[bondCount] = atof(strncpy(token,line+lineCount*16,16));
							bondCount++;
							lineCount++;
						}
					}
					// make sure it worked - DEBUG
					for (i=0;i<bonds.nTypes;i++) {
						printf("Bond type %d has equilibrium value %f\n", i+1, bonds.bondX0Unique[i]);
					}
				} else if (strcmp(flag,bondKFlag) == 0) {
					// read bond k values
					nLines = (int) bonds.nTypes / 5.0 + 1;
					printf("number of lines to read for bond force constant: %d\n", nLines);
					/* skip format line */
					fgets(line, MAXCHAR, prmFile);
					/* loop over lines */
					bondCount = 0;
					for (i=0;i<nLines;i++) {
						fgets(line, MAXCHAR, prmFile);
						lineCount = 0;
						while (bondCount < bonds.nTypes && lineCount < 5) {
							bonds.bondKUnique[bondCount] = atof(strncpy(token,line+lineCount*16,16));
							bondCount++;
							lineCount++;
						}
					}
					// make sure it worked - DEBUG
					for (i=0;i<bonds.nTypes;i++) {
						printf("Bond type %d has force constant %f\n", i+1, bonds.bondKUnique[i]);
					}
				}			
			}
		}
		fclose( prmFile );
	}

}




