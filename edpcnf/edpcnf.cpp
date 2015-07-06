/**

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <vector>

#include "../inc/cnf.cpp"

typedef std::vector< std::pair<int,int> > edges;

int main(int argc, char *argv[])
{

    //default values for parameters
    unsigned int k; //number of elements in +-1-sequence
    unsigned int s = time(NULL); //seed
    bool three=0,help=0,kset=0;

    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"k:3s:")) != -1){
        switch(opt){
        case 'k': k=atoi(optarg); kset=1; break;
        case '3': three=1; break;
        case 's': s=atoi(optarg); break;
        default: help=1;
        }
    }

    //show help if parameters are wrong
    if (help or !kset) {
        fprintf(stderr,"Usage: %s [options]\n",argv[0]);
        fprintf(stderr,"\n");
        fprintf(stderr,"%s constructs a (satisfiable) SAT formula in CNF, that is reduced from\n",argv[0]);
        fprintf(stderr,"a Erdös Discrepancy Problem instance.\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"Options:\n");
        fprintf(stderr," -h    This help text.\n");
        fprintf(stderr," -k ?  Number of elements in +-1-sequence.\n");
        fprintf(stderr," -3 ?  Formula is in 3-CNF.\n");
        fprintf(stderr," -s ?  Seed for random numbers. Default: timestamp\n");
        exit(0);
    }

    printf("c k=%d\n",k);

    CNF formula;

    int e = 1;
    int t = e + k + 1;

    for (int d=1; d<=k; d++)
    {
        for (int j=2; j<=k/d; j+=2)
        {
            printf("d=%d, j=%d\n",d,j);
            int x1 = e + d*(j-1);
            int x2 = e + d*j;
            int y1 = t++;
            int y2 = y1+2;
            int z1 = t++;
            int z2 = z1+2;
            formula.add(std::vector<int> {-x1, x2, -y1, y2, x1, -x2, -y1, y2});
            formula.add(std::vector<int> {-x1, -x2, -y1, -y2});
            formula.add(std::vector<int> {x1, x2, -y1, e});
            formula.add(std::vector<int> {-x1, x2, y1, z1, -y2, x1, -x2, y1, z1, -y2});
            formula.add(std::vector<int> {-x1, x2, y1, z1, -z2, x1, -x2, y1, z1, -z2});
            formula.add(std::vector<int> {-x1, -x2, y1, z1, z2});
            formula.add(std::vector<int> {x1, x2, y1, z1, y2});
            formula.add(std::vector<int> {-x1, x2, -z1, z2, x1, -x2, -z1, z2});
            formula.add(std::vector<int> {-x1, -x2, -z1, e});
            formula.add(std::vector<int> {x1, x2, -z1, -z2});
            formula.add(std::vector<int> {-y1, -z1});
        }
    }

    formula.add(std::vector<int> {-e});

    if (three) {
        formula.tseitin().write(stdout);
    } else {
        formula.write(stdout);
    }

    return 0;
}
