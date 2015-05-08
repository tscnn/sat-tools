/**

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <new>
#include <algorithm>
#include <time.h>

int main(int argc, char *argv[])
{
    //default values for parameters
    int n = 0; //number of vertices
    double d = 0.5; //probability for every edge
    unsigned int s = time(NULL); //seed
    bool help = false; //show help?
    
    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"n:d:s:")) != -1){
        switch(opt){
        case 'n': n=atoi(optarg); break;
        case 'd': d=atof(optarg); break;
        case 's': s=atoi(optarg); break;
        default: help=true;
        }
    }
    
    //show help if parameters are wrong
    if (optind == 1 || help || n < 0 || d < 0 || d > 1) {
        fprintf(stderr,"Usage: %s [options]\n\n",argv[0]);
        fprintf(stderr,"%s constructs a SAT formula in CNF, that is reduced from a\nrandom hypergraph.\n\n",argv[0]);
        fprintf(stderr,"Options:\n");
        fprintf(stderr," -h    This help text.\n");
        fprintf(stderr," -n ?  Number of vertices.\n");
        fprintf(stderr," -d ?  Edge probability, a float between 0 and 1. Default: 0.5\n");
        fprintf(stderr," -s ?  Seed for random numbers. Default: timestamp\n");
        exit(0);
    }
    
    printf("c n=%d\n",n);
    printf("c d=%f\n",d);
    printf("c s=%d\n",s);
    
    //init adjacency matrix for the hypergraph
    bool *adj;
    try{
        adj = new bool[n*n*n];
    }
    catch(std::bad_alloc& ba)
    {
	    fprintf(stderr,"Cannot allocate memory for adjacency matrix: %s\n",ba.what());
        exit(0);
    }

    int nbedges = 0;

    //construct the hypergraph
    
    //iterate all possible edges
    for(int i=0; i<n; i=i+3) {
        for(int j=1; j<n; j=j+3) {
            for(int k=2; k<n; k=k+3) {
            
                if (RAND_MAX*d >= rand_r(&s)) {
                    nbedges++;
                    adj[i*n*n + j*n + k] = true;
                } else {
                    adj[i*n*n + j*n + k] = false;
                }
                
            }
        }
    }
    
    //print the formula
    printf("p cnf %d %d\n",3*n,3*nbedges+n);
    
    //iterate all vertices and print the reduced clause
    for(int v=0; v<n; v++) {
        printf("%d %d %d 0\n", 3*v+1, 3*v+2, 3*v+3);
    }
    
    //iterate all edges and print the reduced clauses
    for(int i=0; i<n; i=i+3) {
        for(int j=1; j<n; j=j+3) {
            for(int k=2; k<n; k=k+3) {
            
                if (adj[i*n*n + j*n + k]) {
                    printf("%d %d %d 0\n", -(3*i+1), -(3*j+1), -(3*k+1));
                    printf("%d %d %d 0\n", -(3*i+2), -(3*j+2), -(3*k+2));
                    printf("%d %d %d 0\n", -(3*i+3), -(3*j+3), -(3*k+3));
                }
                
            }
        }
    }

    return 0;
}
