#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "matrixops.h"
#include "node.h"
/*
#define DTau (2.5e-5)
#define DTSQUARED (6.25e-10)
#define DAMPING 1
#define STIFFNESS 100
*/
using namespace std;

//Global Variables
double DTau;
double TFinal;
double DTauSqd;
double TwiceDTau;
double *CurDisplacement;
double *LastDisplacement;
double *Force;

//Select is used to choose double derivative, derivative, or proportional (2,1, or 0)
void selfrefAssemble(Node*list,double**m,int select, int NCNT, int size)
{
    zero(m,size);
    for(int i=0;i<NCNT;i++)
    {
        m[i][i] = list[i].getselffactor(select);
        m[i+1][i+1] = m[i][i];
        i++;
    }
}

//Select is used to choose double derivative, derivative, or proportional (2,1, or 0)
//It is assumed that the dependant variable (ex. force) is only transferred axially
//transformation matrix is passed as a parameter so that it can be used multiple
//times without recalculating
void coupledAssemble(Node*list,double**c,double**transformation,int select, int NCNT, int DoF)
{
    zero(c,DoF*NCNT);
    for(int cnt=0;cnt<NCNT;cnt++)
    {
        for(int cnum=0;cnum<list[cnt].getconn();cnum++)
        {
            addLocToGlo(c,transformation,cnt,list[cnt].connto(cnum),DoF,list[cnt].getconnfactor(cnum,select));
        }
    }
}

// matrices named for M, C, and K for visualization purposes
void GAssemble(int size, double**M, double**C, double**K, double*G)
{
    double **temp = CreateMatrix(size), **temp2 = CreateMatrix(size);//may make this a parameter so that memory is not constantly being allocated and deallocated
    mulsca(M,temp,size,size,(2*DTauSqd));
    subm(temp,K,temp,size,size);
    mulsquvec(temp,CurDisplacement,G,size);
    mulsca(M,temp,size,size,(-DTauSqd));
    mulsca(C,temp2,size,size,(TwiceDTau));
    addm(temp,temp2,temp,size,size);
    mulsquvec(temp,LastDisplacement,temp2[0],size);
    for(int i = 0;i<size;i++)
    {
        G[i] += Force[i] + temp2[0][i];
    }
    DeleteMatrix(size,temp);
    DeleteMatrix(size,temp2);
    temp = temp2 = NULL;
}
void AAssemble(int size, double**M, double**C,double**A)
{
    double **temp = CreateMatrix(size);
    mulsca(M,temp,size,size,DTauSqd);
    mulsca(C,A,size,size,TwiceDTau);
    addm(A,temp,A,size,size);
    DeleteMatrix(size,temp);
}

int main()
{
    //Initialization.
    int NCNT, DoF;
    Node*nodes = NULL;

    //set up timestep values
    cout << "This Program solves a system of 2nd order (no bending allowed) constant term ODEs using FEM" << endl;
    cout << "Enter the timestep in seconds." << endl;
    cin >> DTau;
    cout << "Enter last time to solve for." << endl;
    cin >> TFinal;
    int cycles = ceil(TFinal/DTau); //Cannot do part of a cycle
    DTauSqd = 1/(DTau*DTau); //Precalculate repeatedly used values
    TwiceDTau = 1/(DTau*2);



    cout<<"Enter 1 to automatically set up the system in problem 4"<<endl;
    cin >> NCNT; //bad place to store this but only temporary

    if(NCNT == 1)
    {
        NCNT = 7;
        DoF = 2;
        nodes = new Node[NCNT];
        for (int i=0;i<NCNT;i++)
        {
            nodes[i].initProb4(i);
        }
    }

    else
    {
        cout << "enter # of nodes:          ";
        cin >> NCNT;
        cout << "enter degrees of freedom:  ";
        cin >> DoF;
        nodes = new Node[NCNT];
        for (int i=0;i<NCNT;i++)
        {
            nodes[i].init(i,DoF);
        }
    }
    int size = NCNT*DoF;
    CurDisplacement = new double[size];
    LastDisplacement = new double[size];
    Force = new double[size];
    double *G = new double[size];
    double **A = CreateMatrix(size);
    double **K = CreateMatrix(size);
    double **C = CreateMatrix(size);
    double **M = CreateMatrix(size);
/*
    for(int i = 0;i<size;i++)
    {
        cout << "Input Forced Dependant for Node"
        Force[i] =
    }
*/

    for (int i = 0;i<cycles;i++)
    {
        GAssemble(size,M,C,K,G);
        AAssemble(size,M,C,A);
        lud(A,size,G);
        //Solve Here
    }
    cout << "no seg faults" << endl;
    cin.get();
    return 0;
}
