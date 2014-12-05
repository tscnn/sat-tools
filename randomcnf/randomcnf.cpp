#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <time.h>
#include <unistd.h>

void swap(int *a, int *b) { 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

class Clause {
    private:
        int lit[3]; //list of literals
        int lit_sorted[3]; //sorted literals needed for < operator
    public:
        //constructor for random clause
        //n: number variables in whole formula
        //seed: for random numbers
        Clause(int n, unsigned int *seed) {
            do {
                for(int i=0; i<3; i++)
                    lit[i] = rand_r(seed)%n + 1;
            } while (lit[0]==lit[1] || lit[1]==lit[2] || lit[0]==lit[2]); 
            for(int i=0; i<3; i++)
                if (rand_r(seed)%2)
                    lit[i] = -lit[i];
            for(int i=0; i<3; i++)
                lit_sorted[i] = lit[i];
            if (lit_sorted[0] < lit_sorted[1]) swap(lit_sorted,lit_sorted+1); 
            if (lit_sorted[0] < lit_sorted[2]) swap(lit_sorted,lit_sorted+2); 
            if (lit_sorted[1] < lit_sorted[2]) swap(lit_sorted+1,lit_sorted+2);
        };
        //this < c?
        bool operator<(Clause c) const {
            if (lit_sorted[0] < c.gets(0)) return true;
            else if (lit_sorted[0] > c.gets(0)) return false;
            else if (lit_sorted[1] < c.gets(1)) return true;
            else if (lit_sorted[1] > c.gets(1)) return false;
            else return lit_sorted[2] < c.gets(2);    
        };
        //get the i-th literal
        int operator[](int i) {
            return lit[i];
        }
        //get the i-th literal of the sorted list
        int gets(int i) {
            return lit_sorted[i];
        }
};

int main(int argc, char** argv){

    int n = -1;
    int m = -1;
    unsigned int s = time(NULL);
    
    int opt;
    while((opt=getopt(argc,argv,"n:m:s:")) != -1){
        switch(opt){
        case 'n': n=atoi(optarg); break;
        case 'm': m=atoi(optarg); break;
        case 's': s=atoi(optarg); break;
        default:
            fprintf(stderr,"Usage: %s -n <nbvars> -m <nbclauses> -s <seed>\nif -m is not set, m=n*4.2\n",argv[0]);
            exit(0);
        }
    }
    
    if (m <= 0)
        m = (int)(n*4.2+0.5);
        
    if (n <= 0)
        fprintf(stderr,"Parameter n must be greater then zero.\n");
    
    printf("p cnf %d %d\n",n,m);
    std::set<Clause> formula;
    
    //generate clauses
    for (int i=0; i<m; i++) {
        while (1) {
            Clause c(n,&s);
            if (formula.count(c) == 0) {
                formula.insert(c);
                printf("%d %d %d 0\n",c[0],c[1],c[2]);
                break;
            }
        }
    }
    
    return 0;
    
}

