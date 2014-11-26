#include <stdio.h>
#include <stdlib.h>
#include <set>

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
    
    //params
    if (argc < 3 || argc > 4) {
        printf("usage: randcnf <SEED> <NBVAR> [<NBCLAUSE>]\nif NBCLAUSE is not set, NBCLAUSE=NBVAR*4.2\n");
        return 0;
    }
    unsigned int seed = atoi(argv[1]);
    int n = atoi(argv[2]),m;
    if (argc == 4)
        m = atoi(argv[3]);
    else
        m = (int)(n*4.2+0.5);
    
    printf("p cnf %d %d\n",n,m);
    std::set<Clause> formula;
    
    //generate clauses
    for (int i=0; i<m; i++) {
        while (1) {
            Clause c(n,&seed);
            if (formula.count(c) == 0) {
                formula.insert(c);
                printf("%d %d %d 0\n",c[0],c[1],c[2]);
                break;
            }
        }
    }
    
    return 0;
    
}

