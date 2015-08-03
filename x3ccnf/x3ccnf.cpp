/**
 * x3c: Given a set X, with |X| = 3q, and a collection C of 3-element subsets
 * of X. Can we find a subset C’ of C where every element of X occurs in
 * exactly one member of C’? 
 */

#include <stdlib.h>
#include <stdio.h>
#include <vector>

void main()
{
    unsigned int n = 9; //size of X
    unsigned int m = 18; //number of 3-subsets
    unsigned int seed = 123;
    
    //construct first part of C
    unsigned int *C = new unsigned int[3*m];
    for (int i=0; i<n; i++)
    {
        C[i] = i;  
    }
    //shuffle first part of C
    for (int i=0; i<n; i++)
    {
        unsigned int tmp = C[i];
        int r = rand_r(&seed) % n;
        C[i] = C[r];
        C[r] = tmp;  
    }
    //construct the rest of C
    for (int i=n; i<3*m; i+=3)
    {
        do {
            U[i] = rand_r(&seed) % n;
            U[i+1] = rand_r(&seed) % n;
            U[i+2] = rand_r(&seed) % n;
        } while (U[i]==U[i+1] || U[i]==U[i+2] || U[i+1]==U[i+2]);          
    }
    
    //print SAT instance to stdout
    //iterate elements in X
    for (int i=0; i<n; i++)
    {
        bool first=1;
        //iterate 3-sets in C
        for (int j=0; j<m; j++)
        {
            if (C[3*j]==i || C[3*j+1]==i || C[3*j+2]==i)
            {
                if (first) first=0; else printf(" ");
                printf("%d",j);
            }
        }
        printf("\n");
    }
    
    delete [] C;
}
