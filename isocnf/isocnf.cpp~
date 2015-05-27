/**

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <new>
#include <algorithm>
#include <time.h>
#include <assert.h>

void shuffle(unsigned int *array, unsigned int len, unsigned int *seed)
{
    for (unsigned int i=0; i<len; i++)
    {
        int r = rand_r(seed) % len;
        unsigned int tmp = array[i];
        array[i] = array[r];
        array[r] = tmp;
    }
}

int main(int argc, char *argv[])
{

    //default values for parameters
    unsigned int n; //number of vertices in subgraph
    unsigned int m; //number of vertices in maingraph
    double p;       //amount of edges that are supposed to remove in subgraph
    unsigned int q; //number of edges in maingraph
    unsigned int s = time(NULL); //seed
    bool help=0,nset=0,mset=0,pset,qset;
    
    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"n:m:p:q:s:")) != -1){
        switch(opt){
        case 'n': n=atoi(optarg); nset=1; break;
        case 'm': m=atoi(optarg); mset=1; break;
        case 'p': p=atof(optarg); pset=1; break;
        case 'q': q=atoi(optarg); qset=1; break;
        case 's': s=atoi(optarg); break;
        default: help=1;
        }
    }
    
    //show help if parameters are wrong
    if (help || !nset || !mset || !pset || !qset) {
        fprintf(stderr,"Usage: %s [options]\n",argv[0]);
        fprintf(stderr,"\n");
        fprintf(stderr,"%s constructs a satisfiable SAT formula in 3-CNF, that is reduced from\n",argv[0]);
        fprintf(stderr,"a random subgraph isomorphism instance.\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"Options:\n");
        fprintf(stderr," -h    This help text.\n");
        fprintf(stderr," -n ?  Number of vertices in subgraph.\n");
        fprintf(stderr," -m ?  Number of vertices in maingraph.\n");
        fprintf(stderr," -p ?  Amount of edges that are supposed to remove in subgraph.\n");
        fprintf(stderr," -q ?  Number of edges in maingraph.\n");
        fprintf(stderr," -s ?  Seed for random numbers. Default: timestamp\n");
        exit(0);
    }
    
    assert(n<=m);
    assert(p<=1);
    assert(p>=0);
    
    printf("c n=%d\n",n);
    printf("c m=%d\n",m);
    printf("c p=%f\n",p);
    printf("c q=%d\n",q);
    
    //generate random maingraph
    bool *main = new bool[m*m];
    int i=0;
    while (i<q)
    {
        int u = rand_r(&s) % m;
        int v = rand_r(&s) % m;
        if (!(main[u*m+v])) {
            main[u*m+v] = 1;
            main[v*m+u] = 1;
            i++;
        }
    }
    
    //choose randomly an induced subgraph from maingraph
    bool *sub = new bool[n*n];
    
    
    return 0;
}
