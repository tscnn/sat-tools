/**
    //create 3-colored graph instance and reduce it without coloring to 3-SAT.
     A1         B1         C1
     A2         B2         C2

     für jeden Knoten i (Beispiel i=A1):
     A1_is_1   A1_is_2   A1_is_3

     für jede Kante ij (Beispiel ij=A1B1):
     A1_is_1 => not B1_is_1
     A1_is_2 => not B1_is_2
     A1_is_3 => not B1_is_3

     a => b  <=>  not a or b
     a => not b  <=>  not a or not b
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <new>

int main(int argc, char *argv[])
{
    //default values for parameters
    int n = 0; //number of vertices
    double d = 0.5; //probability for every edge
    unsigned int s = time(NULL); //seed
    
    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"n:d:s:")) != -1){
        switch(opt){
        case 'n': n=atoi(optarg); break;
        case 'd': d=atof(optarg); break;
        case 's': s=atoi(optarg); break;
        default:
            fprintf(stderr,"Usage: %s ... \n",argv[0]);
            exit(0);
        }
    }
    
    //init adjacency matrix for the hypergraph
    bool *adj;
    try{
        adj = new bool[n*n*n];
    }
    catch(std::bad_alloc&)
    {
	    fprintf(stderr,"Error: Allocating memory for adjacency matrix failed.\n");
        exit(0);
    }

    int nbedges = 0;

    //construct the hypergraph
    
    //iterate all possible edges
    for(int i=0; i<n; i=i+3) {
        for(int j=1; j<n; j=j+3) {
            for(int k=2; k<n; k=k+3) {
            
                if (RAND_MAX*d>=rand_r(&s)) {
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
