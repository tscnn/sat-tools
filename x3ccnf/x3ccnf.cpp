/**
 * x3c: Given a set X, with |X| = 3q, and a collection C of 3-element subsets
 * of X. Can we find a subset C’ of C where every element of X occurs in
 * exactly one member of C’?
 */

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <assert.h>

#include "../inc/cnf.cpp"

int main(int argc, char **argv)
{
    unsigned int n = 0; //size of X
    unsigned int m = 0; //size of C
    unsigned int seed = time(NULL); //seed
    bool three=0; //if true we output a 3-CNF instance
    bool help=0; //show help
    bool nset=0,mset=0;

    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"n:m:3s:")) != -1)
    {
        switch(opt)
        {
            case 'n': n=atoi(optarg); nset=1; break;
            case 'm': m=atoi(optarg); mset=1; break;
            case '3': three=1; break;
            case 's': seed=atoi(optarg); break;
            default: help=1;
        }
    }

    //show help if parameters are wrong
    if (help or !nset or !mset)
    {
        fprintf(stderr,"Usage: %s [options]\n",argv[0]);
        fprintf(stderr,"\n");
        fprintf(stderr,"%s constructs a satisfiable SAT instance in CNF, that is\n",argv[0]);
        fprintf(stderr,"reduced from a random x3c (exact cover) instance.\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"Options:\n");
        fprintf(stderr," -h    This help text.\n");
        fprintf(stderr," -n ?  Size of the set to be covered. Must be positive and a multiple of 3.\n");
        fprintf(stderr," -m ?  Size of the collection. Must be positive.\n");
        fprintf(stderr," -3    Reduce to 3-CNF instance.\n");
        fprintf(stderr," -s ?  Seed for random numbers. Default: timestamp\n");
        exit(0);
    }

    assert(n > 0);
    assert(m > 0);
    assert(n%3 == 0);

    //construct first part of C
    unsigned int *C = new unsigned int[3*m];
    for (unsigned int i=0; i<n; i++)
    {
        C[i] = i;
    }
    //shuffle first part of C
    for (unsigned int i=0; i<n; i++)
    {
        unsigned int tmp = C[i];
        int r = rand_r(&seed) % n;
        C[i] = C[r];
        C[r] = tmp;
    }
    //construct the rest of C
    for (unsigned int i=n; i<3*m; i+=3)
    {
        do {
            C[i] = rand_r(&seed) % n;
            C[i+1] = rand_r(&seed) % n;
            C[i+2] = rand_r(&seed) % n;
        } while (C[i]==C[i+1] || C[i]==C[i+2] || C[i+1]==C[i+2]);
    }

    CNF cnf;

    //reduce to CNF

    //iterate elements in X
    for (unsigned int i=0; i<n; i++)
    {
        std::vector<int> clause;
        //iterate 3-sets in C
        for (unsigned int j=0; j<m; j++)
        {
            if (C[3*j]==i or C[3*j+1]==i or C[3*j+2]==i)
            {
                clause.push_back(j+1);
            }
        }
        cnf.add(clause);
    }

    //iterate 3-sets in C
    for (unsigned int i=0; i<m; i++)
    {
        //iterate 3-sets in C
        for (unsigned int j=i+1; j<m; j++)
        {
            //have ci,cj in C a common element?
            if (C[3*j]==C[3*i] or C[3*j]==C[3*i+1] or C[3*j]==C[3*i+2] or
                C[3*j+1]==C[3*i] or C[3*j+1]==C[3*i+1] or C[3*j+1]==C[3*i+2] or
                C[3*j+2]==C[3*i] or C[3*j+2]==C[3*i+1] or C[3*j+2]==C[3*i+2])
            {
                std::vector<int> clause;
                clause.push_back(-(i+1));
                clause.push_back(-(j+1));
                cnf.add(clause);
            }
        }
    }

    if (three) {
        cnf.tseitin().write(stdout);
    } else {
        cnf.write(stdout);
    }

    delete [] C;
    return 0;
}
