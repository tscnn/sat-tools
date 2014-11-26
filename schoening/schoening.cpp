#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <time.h>
#include <vector>

//#define LOG

int main(int argc, char **argv){
    
    unsigned int nbprocs=4;
    
    //read from file or from stdin
    FILE *fp;
    if(argc>=2) fp=fopen(argv[1],"r");
    else fp=stdin;
    
    //skip comments
    while((fgetc(fp))!='p')
        while(fgetc(fp)!='\n'){}
    
    //read head
    unsigned int n,m;
    if(fscanf(fp," cnf %d %d\n",&n,&m)!=2){
        printf("cannot read input");
        exit(0);
    }
    
    //read clauses
    std::vector<int> clauses[m];
    unsigned int k=0;
    for(int i=0; i<m; i++){
        int u;
        do{
            if(fscanf(fp,"%d",&u)!=1){
                printf("cannot read input");
                exit(0);
            }
            if(u!=0) clauses[i].push_back(u);
        }while(u!=0);
        if(k<clauses[i].size())
            k=clauses[i].size();
    }
    
    //print clauses
    /*for(int i=0; i<m; i++){
        for(int j=0; j<clauses[i].size(); j++){
            printf("%d ",clauses[i][j]);
        }
        printf("\n");
    }*/
    
    unsigned int *seed = new unsigned int[nbprocs];
    seed[0]=time(NULL);
    for(int i=1; i<nbprocs; i++)
        seed[i]=rand_r(seed);
    
    /*
    mpz_t is a integer type without limitation.
    mpz_init(x) initialize x and set it to zero.
    mpz_clear(x) free the space that x uses.
    mpz_ui_pow_ui(x,b,e) calculates x=b^e. b,e are unsigned ints.
    mpz_add_ui(x,y,n) calculates x=y+n. x,y are mpz_t and n are unsigned int.
    */
    mpz_t s,t;
    mpz_init(s);
    mpz_init(t);
    mpz_ui_pow_ui( s, 2, (unsigned int) ceil(log2(2.0-2.0/k)*n) );
    mpz_cdiv_q_ui(t,s,nbprocs);
    
    #ifdef LOG
        printf("c nbproc=%d\n",nbprocs);
        printf("c n=%d\n",n);
        printf("c m=%d\n",m);
        printf("c k=%d\n",k);
        printf("c b=%f\n",log2(2.0-2.0/k)*n);
        printf("c s=");mpz_out_str(stdout,10,s);printf("\n");
        printf("c t=");mpz_out_str(stdout,10,t);printf("\n");
    #endif

    bool global_sat=false;
    
    //parallelization with openmp
    #pragma omp parallel for
    for(unsigned int proc=0; proc<nbprocs; proc++){
    
        #ifdef LOG
            printf("c i am worker #%d\n",proc);
        #endif
        
        //assignment
        unsigned int *a = new unsigned int[n];
        //counters
        unsigned int j,l,p,r,v;
        //literal
        int u;
        //local sat
        bool sat;
        //unlimited counter
        mpz_t i;
        
        //schoenings algorithm
        for( mpz_init(i),sat=false ; mpz_cmp(t,i)>0 && !sat && !global_sat ; mpz_add_ui(i,i,1) ){
            
            //random assignment
            for(j=0;j<n;j++)
                a[j]=rand_r(seed+proc)%2;
            
            #ifdef LOG
                #pragma omp critical
                {
                    printf("c worker #%d walking randomly #",proc);
                    mpz_out_str(stdout,10,i);
                    printf("\n");
                }
            #endif
            
            //random walk until 3n steps are done or a satisfying assignment is reached
            for(j=0; j<3*n && !sat; j++){
                
                //test assignment
                for(l=0,sat=true; l<m && sat; l++){//iter over clauses until unsat is found
                                                   //or all clauses are tested
                
                    for(p=0,sat=false; p<clauses[l].size() && !sat; p++){//iter over literals
                                                                         //until sat literal is found
                                                                         //or all literals are tested
                        u=clauses[l][p];
                        sat=(u>0 ^ a[abs(u)-1]==0);
                    }
                    
                }
                l--;//now l is the index of the found unsat clause
                
                #ifdef LOG
                    //print assignment
                    #pragma omp critical
                    {
                        printf("c worker #%d ",proc);
                        for(p=0;p<n;p++) printf("%d",a[p]);
                        printf(sat?" satisfies ! ! ! ! ! ! ! ! ! ! ! !\n":" satisfies not\n");
                    }
                #endif
                
                //doing a step in random walk (flipping the assignment for a variable)
                if(!sat){
                    r=rand_r(seed+proc)%clauses[l].size();
                    v=abs(clauses[l][r])-1;
                    a[v]=1-a[v];
                    #ifdef LOG
                        #pragma omp critical
                        {
                            printf("c worker #%d choosing clause #%d=(",proc,l);
                            //print clause
                            for(p=0;p<clauses[l].size();p++){
                                printf("%d",clauses[l][p]);
                                if(p<clauses[l].size()-1) printf(",");
                            }
                            printf(") and literal #%d=%d\n",r,clauses[l][r]);
                        }
                    #endif
                }
            }
        }
    
        if(!global_sat && sat){
            global_sat=true;
            printf("formula is satisfiable with ");
            for(j=0;j<n;j++) printf("%d",a[j]);
            printf("\n");
        }
    }
    
    if(!global_sat)
        printf("(with very big probability) formula is not satisfiable\n");
    
}
