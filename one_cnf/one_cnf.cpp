/**

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <new>
#include <algorithm>
#include <time.h>

unsigned int csat(int x, int y, int z, unsigned int a)
{
    unsigned int r=0;
    if (((bool)(a & (1<<(abs(x)-1)))) == x>0) r++;
    if (((bool)(a & (1<<(abs(y)-1)))) == y>0) r++;
    if (((bool)(a & (1<<(abs(z)-1)))) == z>0) r++;
    return r;
}

void printa(unsigned int a, unsigned int n)
{
    for (int i=n-1; i>=0; i--)
    {
        printf(((a>>i) & 1) ? "1" : "0");
    }
}

bool check_assignment(unsigned int a, int n)
{
    int sum=0;
    for (unsigned int i=0; i<n; i++)
    {
        if (a & 1) sum++;
        a >>= 1;
    }
    return sum==n/2;
}

bool check_clauses(int *F, unsigned int m)
{
    int x,y,z;
    for (unsigned int i=0; i<3*m; i+=3)
    {
        x=F[i];
        y=F[i+1];
        z=F[i+2];
        if (abs(x)==abs(y) || abs(x)==abs(z) || abs(y)==abs(z))
        {
            return 0;
        }
    }
    return 1;
}

unsigned int check_clauses2(int *F, unsigned int n, unsigned int m, unsigned int a)
{
    return 1;
    unsigned int nb = 0;
    for (unsigned int i=0; i<3*m; i+=3)
    {
        if (csat(F[i],F[i+1],F[i+2],a) == 3)
        {
            nb++;
        }
    }
    return nb;
}

int main(int argc, char *argv[])
{

    //default values for parameters
    unsigned int n = 0; //number of vertices
    unsigned int m = 0; //probability for every edge
    unsigned int s = time(NULL); //seed
    bool help=0,nset=0,mset=0;
    
    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"n:m:s:")) != -1){
        switch(opt){
        case 'n': n=atoi(optarg); nset=1; break;
        case 'm': m=atoi(optarg); mset=1; break;
        case 's': s=atoi(optarg); break;
        default: help=1;
        }
    }
    
    //show help if parameters are wrong
    if (help || !nset || !mset) {
        fprintf(stderr,"Usage: %s [options]\n\n",argv[0]);
        fprintf(stderr,"%s constructs a SAT formula in CNF, that is reduced from a\nrandom hypergraph.\n\n",argv[0]);
        fprintf(stderr,"Options:\n");
        fprintf(stderr," -h    This help text.\n");
        fprintf(stderr," -n ?  Number of variables.\n");
        fprintf(stderr," -m ?  Number of clauses.\n");
        fprintf(stderr," -s ?  Seed for random numbers. Default: timestamp\n");
        exit(0);
    }
    
    printf("c s=%d\n",s);
    
    int F[3*m];
    unsigned int nba = 0;
    unsigned int solution = 1;
    
    for (int i=0; i<3*m; i++)
    {
        F[i] = (i%(2*n))-n;
        if (F[i]>=0) F[i]++;
    }
    
    while (nba != 1 or !check_assignment(solution,n) or check_clauses2(F,n,m,solution) > 100)
    {
        do {
            for (int i=0; i<3*m; i++)
            {
                int tmp = F[i];
                int r = rand_r(&s) % 3*n;
                F[i] = F[r];
                F[r] = tmp;
            }
        } while (!check_clauses(F,m));
        //test assignments
        nba = 0;
        for (unsigned int a=0; a<(2<<(n-1)) && nba<=1; a++)
        {
        
            bool sat=1;
            for (int i=0; i<3*m; i+=3)
            {
                if (csat(F[i],F[i+1],F[i+2],a) == 0)
                {
                    sat=0;
                }
            }
            if (sat) {
                solution = a;
                nba++;
            }
        }
        
    }
    
    printf("c %d assignment: ",nba); printa(solution,n); printf("\n");
    printf("c %d fullsat clauses\n",check_clauses2(F,n,m,solution));
    
    printf("p cnf %d %d\n",n,m);
    for (int i=0; i<3*m; i+=3)
        printf("%d %d %d 0\n",F[i],F[i+1],F[i+2]);
    
    return 0;
}
