
#include <stdio.h>
#include <stdlib.h>
//#include <cuda.h>
//#include <cuda_runtime.h>
#include <math.h>

#define nDim 3

class bond
{
	public:
		int nBonds;
		int nTypes;
		int *bondType;
		int *bondAtoms;
		int *bondks;
		int *bondx0s;

};
