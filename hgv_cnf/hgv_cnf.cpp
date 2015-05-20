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
    unsigned int n = 0; //number of vertices
    unsigned int d = 2; //probability for every edge
    unsigned int s = time(NULL); //seed
    bool help = false; //show help?
    
    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"n:d:s:")) != -1){
        switch(opt){
        case 'n': n=atoi(optarg)/2*2; break;
        case 'd': d=atoi(optarg); break;
        case 's': s=atoi(optarg); break;
        default: help=true;
        }
    }
    
    //show help if parameters are wrong
    if (optind == 1 || help) {
        fprintf(stderr,"Usage: %s [options]\n\n",argv[0]);
        fprintf(stderr,"%s constructs a SAT formula in CNF, that is reduced from\nvertex cover.\n\n",argv[0]);
        fprintf(stderr,"Options:\n");
        fprintf(stderr," -h    This help text.\n");
        fprintf(stderr," -n ?  Number of vertices.\n");
        fprintf(stderr," -d ?  Number of edges for each vertex in the vertex cover.\n");
        fprintf(stderr,"         Default: 2\n");
        fprintf(stderr," -s ?  Seed for random numbers. Default: timestamp\n");
        exit(0);
    }
    
    printf("c n=%d\n",n);
    printf("c d=%d\n",d);
    printf("c s=%d\n",s);
    
    printf("p cnf %d %d\n",n,(d+1)*n/2);
    
    for (int v=1; v<=n/2-2; v+=3)
    {
        printf("%d %d %d 0\n",v,v+1,v+2);
    }
    
    for (int v=1; v<=n/2; v++) //iterate vertexes, that building a vertex cover
    {
        //construct clause not v_i or not v_i+1 or not v_2i (v_2i is not in the vertex cover)
        printf("%d %d %d 0\n",-v,((v<(n/2))?-(v+1):-1),-(v+n/2));
        
        for (int i=0; i<d; i++)
        {   
            int u = 1 + n/2 + (rand_r(&s) % (n/2));
            int w = 1 + n/2 + (rand_r(&s) % (n/2-1));
            if (w >= u) w++;
            printf("%d %d %d 0\n",u,v,w);
            //int u = 1 + (rand_r(&s) % (n-1));
            //int w = 1 + (rand_r(&s) % (n-2));
            //if (u >= v) u++;
            //if (w >= v) w++;
            //if (w >= u) w++;
            //printf("%d %d %d 0\n",u,v,w);
        }
    }

    return 0;
}
