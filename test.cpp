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
/*
void mAssemble(Node*list,double**m)
{
    for(int i=0;i<NCNT;i++)
    {
        m[i][i] = list[i].getMass();
        m[i+1][i+1] = m[i][i];
        i++;
    }
}

void cAssemble(Node*list,double**c)
{
    double**transformation = CreateMatrix(4);
    double a, b;
    zero(c,2*NCNT);
    for(int cnt=0;cnt<NCNT;cnt++)
    {
        for(int cnum=0;cnum<list[cnt].getconn();cnum++)
        {
            a = list[cnt].getCos(list[(list[cnt].connto(cnum))]);
            b = list[cnt].getSin(list[(list[cnt].connto(cnum))]);
            trans(a,b,transformation);
            mulsca(transformation,4,4,DAMPING);
            addLocToGlo(c,transformation,cnt,list[cnt].connto(cnum));
        }
    }
    DeleteMatrix(4,transformation);
    transformation = NULL;
}

void kAssemble(Node*list,double**k)
{
    double**transformation = CreateMatrix(4);
    double a, b;
    zero(k,2*NCNT);
    for(int cnt=0;cnt<NCNT;cnt++)
    {
        for(int cnum=0;cnum<list[cnt].getconn();cnum++)
        {
            a = list[cnt].getCos(list[(list[cnt].connto(cnum))]);
            b = list[cnt].getSin(list[(list[cnt].connto(cnum))]);
            trans(a,b,transformation);
            mulsca(transformation,4,4,STIFFNESS);
            addLocToGlo(k,transformation,cnt,list[cnt].connto(cnum));
        }
    }
    DeleteMatrix(4,transformation);
    transformation = NULL;
}
*/
// matrices named for G, C, and K
void GAssemble{int size, double**

}
int main()
{
    cout << "This Program solves a system of 2nd order (no bending allowed) constant term ODEs using FEM" << endl;
    double DTau;
    cout << "Enter the timestep in seconds." << endl;
    cin >> DTau;
    double DTauSqd = DTau*DTau;
    double TwiceDTau = DTau*2;
    cout << TwiceDTau;
    int NCNT, DoF;
    Node*nodes = NULL;
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
    cout << "no seg faults" << endl;
    cin.get();
    return 0;
}
