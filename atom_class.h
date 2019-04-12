
#include <stdio.h>
#include <stdlib.h>
//#include <cuda.h>
//#include <cuda_runtime.h>
#include <math.h>

#define nDim 3

class atom
{
	private:
		int i,k;
		FILE *forceXyzFile;
		FILE *xyzFile;
		//float rand_gauss();
	public:
		int nAtoms;
		int nAtomTypes;
		int nAtomBytes;
		int nTypeBytes;
		float *xyz_h;    // coordinate array - host data
		float *xyz_d;    // coordinate array - device data
		float *f_h;      // force array - host data
		float *f_d;      // force array - device data
		float *v_h;      // velocity array - host data
		float *v_d;      // velocity array - device data
		float *mass_h;      // mass array - host data
		float *mass_d;      // mass array - device data
		int *ityp_h;     // atom type array - host data
		int *ityp_d;     // atom type array - device data
		float *x0_h;     // center position of parabola and g - host data 
		float *x0_d;     // center position of parabola and g - device data
		float *g0_h;     // height of parabola approximation of g - host data 
		float *g0_d;     // height of parabola approximation of g - device data
		float *gr2_h;     // excluded volume distance and end of parabola distance squared - host data 
		float *gr2_d;     // excluded volume distance and end of parabola distance squared - device data
		float *w_h;      // width of parabola - host data
		float *w_d;      // width of parabola - device data
		float *alpha_h;  // alpha parameter for g - host data
		float *alpha_d;  // alpha parameter for g - device data
		float *charges_h;    // coordinate array - host data
		float *charges_d;    // coordinate array - device data
		float *lj_A_h;   // Lennard-Jones A parameter - host data
		float *lj_A_d;   // Lennard-Jones A parameter - device data
		float *lj_B_h;   // Lennard-Jones B parameter - host data
		float *lj_B_d;   // Lennard-Jones B parameter - device data
		float sigma;
		int   *key;
		
		// initialize all arrays on CPU memory
		//void initialize(float T, float lbox);
		// initialize all arrays on GPU memory
		//void initialize_gpu();
		// copy parameter arrays to GPU
		//void copy_params_to_gpu();
		// copy position, force and velocity arrays to GPU
		//void copy_pos_v_to_gpu();
		// copy position, force, and velocity arrays from GPU
		//void get_pos_f_v_from_gpu();
		// copy position, and velocity arrays from GPU
		//void get_pos_v_from_gpu();
		// print positions
		//void print_xyz();
		// print forces
		//void print_forces();
		// reorder
		//void reorder();
		// free all arrays on CPU memory
		//void free_arrays();
		// free all arrays on GPU memory
		//void free_arrays_gpu();

		
};
