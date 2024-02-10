//
// This file is part of Heat Gauss Seidel  and is licensed under the terms contained in the COPYING file.
// Copyright (C) 2015-2020 Barcelona Supercomputing Center (BSC)
//
#ifndef __HEAT__
#define __HEAT__
#include <stdio.h>
// configuration

#define NUM_ITER 10
#define ALGORITHM 1
#define RESOLUTION 16384
#define NP (RESOLUTION+2)
#define bx (NP/NB)
#define by (NP/NB)
#define sx NP
#define sy NP

typedef struct
{
    float posx;
    float posy;
    float range;
    float temp;
}
heatsrc_t;

typedef struct
{
    unsigned maxiter;       // maximum number of iterations
    unsigned resolution;    // spatial resolution
    int algorithm;          // 0=>Jacobi, 1=>Gauss

    unsigned visres;        // visualization resolution
  
    double *u, *uhelp;
    double *uvis;

    unsigned   numsrcs;     // number of heat sources
    heatsrc_t *heatsrcs;
}
algoparam_t;

// function declarations

// misc.c
int initialize( algoparam_t *param );
int finalize( algoparam_t *param );
void write_image( FILE * f, double *u,
		  unsigned sizex, unsigned sizey );
int coarsen(double *uold, unsigned oldx, unsigned oldy ,
	    double *unew, unsigned newx, unsigned newy );
int read_input( FILE *infile, algoparam_t *param );
void print_params( algoparam_t *param );
double wtime();

// solvers in solver.c
// double relax_redblack( double *u,
// 		  unsigned sizex, unsigned sizey );
//
// double relax_jacobi( double *u, double *utmp,
// 		   unsigned sizex, unsigned sizey );
#ifndef CUDA 		   
inline __attribute__((always_inline)) double relax_gauss(double *u);

#else
double relax_gauss(double **u, unsigned sizex, unsigned sizey);
#endif // CUDA
#endif // __HEAT__
