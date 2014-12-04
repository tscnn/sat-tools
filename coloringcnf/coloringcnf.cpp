/*
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

int main(int argc, char *argv[])
{
    int n = 0;
    double d = 0.5;
    unsigned int s = time(NULL);
    
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
    
    bool *adj = new bool[n*n];
    int nbedges = 0;
    
    //Generate a random graph. All edges between vertices of different color
    //have probability of d. The color of a vertice i is i%3.
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if (i%3 == j%3) {
                adj[i*n+j] = false;
            } else {
                if ((RAND_MAX + 1) * dist > rand_r(&s)) {
                    adj[i*n+j] = true;
                    nbedges++;
                }
            }
        }
    }
    
    printf("c A 3-SAT formula reduced from an instance for 3-COLORING.\n");
    printf("c Construction parameters: n=%d, d=%f\n",n,d);
    printf("p cnf %d %d\n",3*n,3*nbedges+n);
    
    //iterate vertices, color of a vertice i is i%3
    for (int i=0; i<n; i++) {
        printf("%d %d %d\n",(3*i),(3*i+1),(3*i+2));
        for (int j=i+1; j<n; j++) {
            if (adj[i*n+j]) {
                printf("%d %d\n",(-3*i),(-3*j));
                printf("%d %d\n",(-3*i+1),(-3*j+1));
                printf("%d %d\n",(-3*i+2),(-3*j+2));
            }    
        }
    }
    
    return 0;
}