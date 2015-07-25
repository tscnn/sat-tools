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
#include <assert.h>

int main(int argc, char *argv[])
{
    unsigned int n = 0;
    double d = 0.5;
    unsigned int s = time(NULL);

    int opt;
    while((opt=getopt(argc,argv,"n:d:s:")) != -1)
    {
        switch(opt)
        {
            case 'n': n=atoi(optarg); break;
            case 'd': d=atof(optarg); break;
            case 's': s=atoi(optarg); break;
        }
    }

    //show help if parameters are wrong
    if (n==0 || d<0 || d>1) {
        fprintf(stderr,"Usage: %s [options]\n",argv[0]);
        fprintf(stderr,"\n");
        fprintf(stderr,"%s constructs a satisfiable SAT formula in 3-CNF, that is\n",argv[0]);
        fprintf(stderr,"reduced from a random 3-COLORING instance.\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"Options:\n");
        fprintf(stderr," -h    This help text.\n");
        fprintf(stderr," -n ?  Number of vertices in graph. Must be positive.\n");
        fprintf(stderr," -d ?  Add each possible edge with probability of 0<=d<=1. Default: 0.5\n");
        fprintf(stderr," -s ?  Seed for random numbers. Default: timestamp\n");
        exit(0);
    }

    bool *adj;
    try{
        adj = new bool[n*n];
    }
    catch(std::bad_alloc&)
    {
        fprintf(stderr,"Error: allocating memory for adjacency matrix failed.\n");
        exit(0);
    }

    int nbedges = 0;

    //Generate a random graph. All edges between vertices of different color
    //have probability of d. The color of a vertice i is i%3.
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if (i%3!=j%3 && d>0 && RAND_MAX*d>=rand_r(&s)) {
                adj[i*n+j] = true;
                nbedges++;
            } else {
                adj[i*n+j] = false;
            }
        }
    }

    printf("c A 3-SAT formula reduced from a random 3-COLORING instance.\n");
    printf("c Construction parameters:\n");
    printf("c n=%d\n",n);
    printf("c d=%f\n",d);

    //print the hidden assignment
    printf("c a=");
    for (int i=0; i<n; i++)
    {
        //three boolean variables for each vertice
        int col0 = i%3==0 ? 1 : 0;
        int col1 = i%3==1 ? 1 : 0;
        int col2 = i%3==2 ? 1 : 0;
        printf("%d%d%d",col0,col1,col2);
    }
    printf("\n");

    printf("p cnf %d %d\n",3*n,3*nbedges+n);

    //iterate vertices, color of a vertice i is i%3
    for (int i=0; i<n; i++) {
        printf("%d %d %d 0\n",(3*i+1),(3*i+2),(3*i+3));
        for (int j=i+1; j<n; j++) {
            if (adj[i*n+j]) {
                printf("%d %d 0\n",-(3*i+1),-(3*j+1));
                printf("%d %d 0\n",-(3*i+2),-(3*j+2));
                printf("%d %d 0\n",-(3*i+3),-(3*j+3));
            }
        }
    }

    return 0;
}
