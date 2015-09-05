/**

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <new>
#include <algorithm>
#include <time.h>
#include <assert.h>
#include <vector>
#include <utility>

#include "../inc/cnf.cpp"
#include "../inc/pr.cpp"

int main(int argc, char *argv[])
{

    //default values for parameters
    unsigned int n; //number of vertices in startgraph
    unsigned int m; //number of vertices to add
    double d;       //amount of edges in startgraph
    bool three=0;
    unsigned int seed = time(NULL); //seed
    bool help=0,nset=0,mset=0,dset=0;

    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"n:m:d:3s:")) != -1)
    {
        switch(opt)
        {
            case 'n': n=atoi(optarg); nset=1; break;
            case 'm': m=atoi(optarg); mset=1; break;
            case 'd': d=atof(optarg); dset=1; break;
            case '3': three=1; break;
            case 's': seed=atoi(optarg); break;
            default: help=1;
        }
    }

    //show help if parameters are wrong
    if (help or !nset or !mset or !dset) {
        fprintf(stderr,"Usage: %s [options]\n",argv[0]);
        fprintf(stderr,"\n");
        fprintf(stderr,"%s constructs a satisfiable SAT formula in CNF, that is reduced from\n",argv[0]);
        fprintf(stderr,"a random subgraph isomorphism instance.\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"Options:\n");
        fprintf(stderr," -h    This help text.\n");
        fprintf(stderr," -n ?  Number of vertices in startgraph.\n");
        fprintf(stderr," -m ?  Number of vertices to add.\n");
        fprintf(stderr," -d ?  Amount of edges in startgraph.\n");
        fprintf(stderr," -s ?  Seed for random numbers. Default: timestamp\n");
        exit(0);
    }

    assert(n > 0);
    assert(d <= 1);
    assert(d >= 0);

    bool *G = new bool[n*n]; //subgraph
    bool *H = new bool[(n+m)*(n+m)]; //maingraph

    for (unsigned int i=0; i<n; i++)
    {
        for (unsigned int j=i+1; j<n; j++)
        {
            bool b = random_bool(d, &seed);
            G[i*n+j] = b;
            H[i*(n+m)+j] = b;
        }
    }

    //iterate the additional vertices
    for (unsigned int i=n; i<n+m; i++)
    {
        //iterate edges to subgraph
        for (unsigned int j=0; j<n; j++)
        {
            bool b = random_bool(d, &seed);
            H[j*(n+m)+i] = b;
            //warning: i,j swapped because we require s<t for an edge (s,t)
        }
        //iterate edges between additional vertices
        for (unsigned int j=i+1; j<n+m; j++)
        {
            bool b = random_bool(d, &seed);
            H[i*(n+m)+j] = b;
        }
    }

    printf("c n=%d\n", n);
    printf("c m=%d\n", m);
    printf("c d=%f\n", d);

    printf("c a=");
    for (unsigned int i=0; i<n; i++)
    {
        for (unsigned int j=0; j<n+m; j++)
        {
            if (i == j)
                printf("1");
            else
                printf("0");
        }
    }
    printf("\n");

    /*printf("c G (size=%u)\n", n);
    for (unsigned int i=0; i<n; i++)
    {
        for (unsigned int j=0; j<n; j++)
        {
            if (G[i*n+j])
            {
                printf("c %u->%u\n", i, j);
            }
        }
    }*/

    /*printf("c H (size=%u)\n", n+m);
    for (unsigned int i=0; i<n+m; i++)
    {
        for (unsigned int j=0; j<n+m; j++)
        {
            if (H[i*(n+m)+j])
            {
                printf("c %u->%u\n", i, j);
            }
        }
    }*/

    CNF cnf;

    for (unsigned int i=0; i<n; i++)
    {
        std::vector<int> clause;
        //printf("c");
        for (unsigned int j=0; j<n+m; j++)
        {
            //printf(" x_%u,%u", i, j);
            clause.push_back(i*(n+m)+j+1);
        }
        //printf("\n");
        cnf.add(clause);
    }

    //printf("c\n");

    for (unsigned int i=0; i<n; i++)
    {
        for (unsigned int j=0; j<n+m; j++)
        {
            for (unsigned int k=j+1; k<n+m; k++)
            {
                //printf("c -x_%u,%u -x%u,%u\n", i, j, i, k);
                std::vector<int> clause;
                clause.push_back(-(i*(n+m)+j+1));
                clause.push_back(-(i*(n+m)+k+1));
                cnf.add(clause);
            }
        }
    }

    //printf("c\n");

    for (unsigned int i=0; i<n+m; i++)
    {
        for (unsigned int j=0; j<n; j++)
        {
            for (unsigned int k=j+1; k<n; k++)
            {
                //printf("c -x_%u,%u -x%u,%u\n", j, i, k, i);
                std::vector<int> clause;
                clause.push_back(-(j*(n+m)+i+1));
                clause.push_back(-(k*(n+m)+i+1));
                cnf.add(clause);
            }
        }
    }

    //printf("c\n");

    for (unsigned int i=0; i<n; i++)
    {
        for (unsigned int j=i+1; j<n; j++)
        {
            if (G[i*n+j])
            {
                for (unsigned int k=0; k<n+m; k++)
                {
                    for (unsigned int l=k+1; l<n+m; l++)
                    {
                        if (!H[k*(n+m)+l])
                        {
                            //printf("c i=%u j=%u; k=%u l=%u\n", i, j, k, l);
                            //printf("c -x_%u,%u -x%u,%u\n", i, k, j, l);
                            //printf("c -x_%u,%u -x%u,%u\n", i, l, j, k);
                            std::vector<int> clause1;
                            clause1.push_back(-(i*(n+m)+k+1));
                            clause1.push_back(-(j*(n+m)+l+1));
                            cnf.add(clause1);
                            std::vector<int> clause2;
                            clause2.push_back(-(i*(n+m)+l+1));
                            clause2.push_back(-(j*(n+m)+k+1));
                            cnf.add(clause2);
                        }
                    }
                }
            }
        }
    }

    if (three) {
        cnf.tseitin().write(stdout);
    } else {
        cnf.write(stdout);
    }

    return 0;
}
