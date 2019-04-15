
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include <cuda.h>
//#include <cuda_runtime.h>

using namespace std;
#include "atom_class.h"
#define nDim 3

void atom::allocate()
{
	// size of xyz arrays
	nAtomBytes = nAtoms*sizeof(float);
	nTypeBytes = nAtomTypes*sizeof(float);
	// allocate atom coordinate arrays
	xyz_h = (float *)malloc(nAtomBytes*nDim);
	// allocate atom velocity arrays
	v_h = (float *)malloc(nAtomBytes*nDim);
	// allocate atom force arrays
	f_h = (float *)malloc(nAtomBytes*nDim);
	// alocate mass array
	mass_h = (float *)malloc(nAtoms*sizeof(float));
	// alocate charge array
	charges_h = (float *)malloc(nAtoms*sizeof(float));
	// allocate key array - atom number
	key = (int *)malloc(nAtoms*sizeof(int));
	// allocate atom type arrays
	ityp_h = (int *)malloc(nAtoms*sizeof(int));
	// allocate atom based parameter arrays
	x0_h = (float *)malloc(nTypeBytes);
	g0_h = (float *)malloc(nTypeBytes);
	gr2_h = (float *)malloc(nTypeBytes*2);
	w_h = (float *)malloc(nTypeBytes);
	alpha_h = (float *)malloc(nTypeBytes);
	lj_A_h = (float *)malloc(nTypeBytes);
	lj_B_h = (float *)malloc(nTypeBytes);
	
}

