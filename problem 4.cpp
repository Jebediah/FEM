#include <cstdlib.h>
#include <cmath.h>
#include <iostream.h>
#include "node.h"
#include "matrixops.h"

#define TRUE 1
#define FALSE 0

//may or may not make these arguments at some point or generalize more
//used to avoid literally millions of unnecessary calculations
#define NCNT 7
#define TIMESTEP 0.000025
#define TIMESTEPSQUARED 6.25e-10
#define 2TIMESTEP 0.00005
#define STIFFNESS 100
#define DAMPING 1

int main()
//initialization first
double *k, *c, *m;
k = new double [4][4][nodenum];
c = new double [4][4][nodenum
for (int i = 0; i<nodenum 
