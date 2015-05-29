/**

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <new>
#include <algorithm>
#include <time.h>
#include <assert.h>
#include <vector>
#include <utility>

#include "../inc/cnf.cpp"

#define var(x,y) (x*m+y+1)

typedef std::vector< std::pair<int,int> > edges;

int main(int argc, char *argv[])
{

    //default values for parameters
    unsigned int n; //number of vertices in subgraph
    unsigned int m; //number of vertices in maingraph
    double p;       //amount of edges that are supposed to remove in subgraph
    double q;       //number of edges in maingraph
    bool three=0;
    unsigned int s = time(NULL); //seed
    bool help=0,nset=0,mset=0,pset=0,qset=0;
    
    //get parameters
    int opt;
    while((opt=getopt(argc,argv,"n:m:p:q:3s:")) != -1){
        switch(opt){
        case 'n': n=atoi(optarg); nset=1; break;
        case 'm': m=atoi(optarg); mset=1; break;
        case 'p': p=atof(optarg); pset=1; break;
        case 'q': q=atof(optarg); qset=1; break;
        case '3': three=1; break;
        case 's': s=atoi(optarg); break;
        default: help=1;
        }
    }
    
    //show help if parameters are wrong
    if (help or !nset or !mset or !pset or !qset) {
        fprintf(stderr,"Usage: %s [options]\n",argv[0]);
        fprintf(stderr,"\n");
        fprintf(stderr,"%s constructs a satisfiable SAT formula in CNF, that is reduced from\n",argv[0]);
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
    assert(q<=1);
    assert(q>=0);    
    
    // 1. construct a random graph H with m vertices and q*binom(m,2) edges.
    // 2. construct a subgraph G of H with n vertices
    
    //map all vertices of H to vertices of G or to -1 ...
    std::vector<int> map(m);
    for (int i=0; i<m; i++) {
        map[i] = i<n ? i : -1;
    }
    //... randomly
    for (int i=0; i<map.size(); i++)
    {
        int r = rand_r(&s) % map.size();
        int tmp = map[i];
        map[i] = map[r];
        map[r] = tmp;
    }
    
    edges Emain;
    edges Esub;
    int qint = 0;
    //generate all possible edges
    for (int i=0; i<m; i++) {
        for (int j=i+1; j<m; j++) {
            Emain.push_back(std::make_pair(i,j));
            qint++;
        }
    }
    qint = (int) (qint*q);
    
    assert(qint<=Emain.size());
    
    //shuffle them
    for (int i=0; i<Emain.size(); i++)
    {
        int r = rand_r(&s) % Emain.size();
        std::pair<int,int> tmp = Emain[i];
        Emain[i] = Emain[r];
        Emain[r] = tmp;
    }
    //copy each of the first q edges to subgraph, if both vertices are in subgraph
    //keep in mind, that only the first q edges exists in the graph, but we need the nonexistent edges later
    for (int i=0; i<qint; i++) {
        int u = Emain[i].first;
        int v = Emain[i].second;
        if (map[u] >= 0 and map[v] >= 0) {
            Esub.push_back(std::make_pair(map[u],map[v]));
        }
    }
    //preserve only the front p-part
    Esub.resize(((int)((1-p)*Esub.size()))+1);
    
    printf("c n=%d\n",n);
    printf("c m=%d\n",m);
    printf("c p=%f\n",p);
    printf("c q=%f\n",q);
    
    CNF formula;
    
    for (int i=0; i<n; i++) {
        std::vector<int> clause;
        for (int j=0; j<m; j++) {
            clause.push_back(var(i,j));
        }
        formula.add(clause);
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            for (int k=j+1; k<m; k++) {
                std::vector<int> clause;
                clause.push_back(-var(i,j));
                clause.push_back(-var(i,k));
                formula.add(clause);
            }
        }
    }

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            for (int k=j+1; k<n; k++) {
                std::vector<int> clause;
                clause.push_back(-var(j,i));
                clause.push_back(-var(k,i));
                formula.add(clause);
            }
        }
    }

    for (edges::iterator it1=Esub.begin(); it1!=Esub.end(); it1++) {
        for (edges::iterator it2=Emain.begin()+qint; it2!=Emain.end(); it2++) {
            int i = it1->first;
            int j = it1->second;
            int k = it2->first;
            int l = it2->second;
            std::vector<int> clause1;
            clause1.push_back(-var(i,k));
            clause1.push_back(-var(j,l));
            formula.add(clause1);
            std::vector<int> clause2;
            clause2.push_back(-var(i,l));
            clause2.push_back(-var(j,k));
            formula.add(clause2);
        }
    }

    if (three) {
        formula.tseitin().write(stdout);
    } else {
        formula.write(stdout);
    }
    
    return 0;
}
