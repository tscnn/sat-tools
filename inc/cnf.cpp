#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

class CNF {
    private:
        std::vector<int> literals;
        std::vector<unsigned int> positions;
        std::vector<unsigned int> sizes;
    public:
        int n;
        int m;
        CNF();
        CNF(FILE* fp);
        void clear();
        void read(FILE* fp);
        void write(FILE* fp);
        int mink();
        int maxk();
        int lit(int clause_index, int literal_index);
        int var(int clause_index, int literal_index);
};

CNF::CNF()
{
    n=0;
    m=0;
}

CNF::CNF(FILE* fp)
{
    read(fp);
}

void CNF::clear()
{
    literals.clear();
    positions.clear();
    sizes.clear();
    n=0;
    m=0;
}

void CNF::read(FILE* fp)
{
    //delete contents
    clear();
    //skip comments
    while((fgetc(fp)) != 'p') {
        while(fgetc(fp) != '\n') {
        }
    }
    //read head
    if(fscanf(fp," cnf %d %d\n",&n,&m) == 2) {
        //prepare vectors
        positions.reserve(m);
        positions[0] = 0;
        sizes.reserve(m);
        //read literals
        int u,i=0;        
        while(i<m && fscanf(fp,"%d",&u)==1) {
            if (u==0) {
                sizes[i] = literals.size() - positions[i];
                if (++i<m) {
                    positions[i] = literals.size();
                }
            } else {
                literals.push_back(u);
            }
        }
    }
}

void CNF::write(FILE* fp)
{
    fprintf(fp,"p cnf %d %d\n",n,m);
    for (int i=0; i<m; i++) {
        for (int j=0; j<sizes[i]; j++) {
            if (j>0) fprintf(fp," ");
            fprintf(fp,"%d",lit(i,j));
        }
        fprintf(fp,"\n");
    }
}

int CNF::mink()
{
    return *std::min_element(sizes.begin(),sizes.end());
}

int CNF::maxk()
{
    return *std::max_element(sizes.begin(),sizes.end());
}

int CNF::lit(int clause_index, int literal_index)
{
    return literals[positions[clause_index] + literal_index];
}

int CNF::var(int clause_index, int literal_index)
{
    return abs(lit(clause_index,literal_index));
}