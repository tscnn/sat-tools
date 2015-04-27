#include <algorithm>

class CNF {
    private:
        int *C; //clauses
        unsigned int n; //number of variables
        unsigned int m; //number of clauses
        unsigned int *k; //k[i] is the number of clauses with i literals
        unsigned int maxk; //max(k)
        unsigned int mink; //min(k)
    public:
        CNF();
        CNF(FILE* fp);
        int* data();
        int maxk();
        int mink();
};

/**
 *
 */
CNF::CNF() {

}

/**
 * Constructor that reads a CNF-formula in DIMACS format from file handle.
 */
CNF::CNF(FILE* fp) {
    //skip comments
    while((fgetc(fp))!='p')
        while(fgetc(fp)!='\n'){}
    //read head
    if(fscanf(fp," cnf %d %d\n",&n,&m)!=2){
        fprintf(stderr,"cannot read input\n");
        exit(0);
    }
    k = new unsigned int[m];
    std::fill_n(k,m,0);
    //read clauses
    std::vector<std::vector<int>> clauses;
    maxk=0;
    mink=UINT_MAX;
    for(int i=0; i<m; i++){
        int u;
        std::vector<int> clause;
        //read line/clause
        do{
            if(fscanf(fp,"%d",&u)!=1){
                fprintf(stderr,"cannot read input\n");
                exit(0);
            }
            if(u!=0) clause.push_back(u);
        }while(u!=0);
        clauses.push_back(clause);
        //update statistics
        int s = clause.size();
        if(maxk<s) maxk=s;
        if(mink>s) mink=s;
        k[s]++;
    }
    //a time-efficient array representation of the formula
    int* f = new int[m*(maxk+1)];
    for(int i=0; i<m; i++){
        f[i*(maxk+1)] = clauses[i].size();
        for(int j=0; j<clauses[i].size(); j++){
            f[i*(maxk+1)+j+1] = clauses[i][j];    
        }
        for(int j=clauses[i].size(); j<maxk; j++){
            f[i*(maxk+1)+j+1] = 0;    
        }
    }
    return f;
}