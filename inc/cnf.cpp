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
    CNF();
    CNF(FILE* fp);
    void clear();
    void read(FILE* fp);
    void write(FILE* fp);
    int n();
    int m();
    unsigned int mink();
    unsigned int maxk();
    int lit(int clause_index, int literal_index);
    int var(int clause_index, int literal_index);
    int size(int clause_index);
    std::vector<int> clause(int index);
    void add(std::vector<int> clause);
    CNF tseitin();
};

CNF::CNF()
{
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
    int header_n;
    int header_m;
    //read head
    if(fscanf(fp," cnf %d %d\n",&header_n,&header_m) == 2) {
        //prepare vectors
        positions.resize(header_m);
        positions[0] = 0;
        sizes.resize(header_m);
        //read literals
        int u,i=0;
        while(i<header_m && fscanf(fp,"%d",&u)==1) {
            if (u==0) {
                sizes[i] = literals.size() - positions[i];
                if (++i<header_m) {
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
    fprintf(fp,"p cnf %d %d\n",n(),m());
    for (int i=0; i<m(); i++) {
        for (int j=0; j<sizes[i]; j++) {
            fprintf(fp,"%d ",lit(i,j));
        }
        fprintf(fp,"0\n");
    }
}

int CNF::n()
{
    int p = *std::max_element(literals.begin(),literals.end());
    int n = *std::min_element(literals.begin(),literals.end());
    return std::max(p,abs(n));
}

int CNF::m()
{
    return positions.size();
}

unsigned int CNF::mink()
{
    return *std::min_element(sizes.begin(),sizes.end());
}

unsigned int CNF::maxk()
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

int CNF::size(int clause_index)
{
    return sizes[clause_index];
}

std::vector<int> CNF::clause(int index)
{
    std::vector<int> clause;
    for (int pos=0; pos<size(index); pos++)
    {
        clause.push_back(lit(index,pos));
    }
    return clause;
}

void CNF::add(std::vector<int> clause)
{
    sizes.push_back(clause.size());
    positions.push_back(literals.size());
    for (int i=0; i<clause.size(); i++)
    {
        literals.push_back(clause[i]);
    }
}

CNF CNF::tseitin()
{
    int var = n();
    CNF f3;
    for (int i=0; i<m(); i++)
    {
        std::vector<int> clause = this->clause(i);
        if (clause.size() <= 3) {
            f3.add(clause);
        } else {
            while (clause.size() > 3) {
                std::vector<int> splitted;
                splitted.push_back(++var);
                splitted.push_back(clause[0]);
                splitted.push_back(clause[1]);
                f3.add(splitted);
                clause[0] = -var;
                clause.erase(clause.begin()+1);
            }
            f3.add(clause);
        }
    }
    return f3;
}
