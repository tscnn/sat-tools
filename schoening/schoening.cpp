#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <time.h>
#include <vector>
#include <unistd.h>
#include <ctype.h>
#include <omp.h>
#include <limits.h>

//#define LOG

int main(int argc, char **argv){

    unsigned int nbprocs=omp_get_num_procs();//number of parallel processes
    bool bflag = false;//if true, choose bigger unsatisfied clauses first, else choose the smaller first

    int opt;
    while ((opt=getopt(argc,argv,"bp:")) != -1)
    {
        switch(opt){
            case 'b':
                bflag = true;
                break;
            case 'p':
                nbprocs = atoi(optarg);
                break;
            case '?':
                if (optopt == 'c')
                    fprintf (stderr,"Option -%c requires an argument.\n",optopt);
                else if (isprint (optopt))
                    fprintf (stderr,"Unknown option `-%c'.\n",optopt);
                else
                    fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
                return 1;
            default:
                abort();
        }
    }
    
    //read from file or from stdin
    FILE *fp;
    if(argc>optind) fp=fopen(argv[optind],"r");
    else fp=stdin;
    
    //skip comments
    while((fgetc(fp))!='p')
        while(fgetc(fp)!='\n'){}
    
    //read head
    unsigned int n,m;
    if(fscanf(fp," cnf %d %d\n",&n,&m)!=2){
        fprintf(stderr,"cannot read input\n");
        exit(0);
    }
    
    //read clauses
    std::vector<int> clauses[m];
    unsigned int maxk=0;
    unsigned int mink=UINT_MAX;
    for(int i=0; i<m; i++){
        int u;
        do{
            if(fscanf(fp,"%d",&u)!=1){
                fprintf(stderr,"cannot read input\n");
                exit(0);
            }
            if(u!=0) clauses[i].push_back(u);
        }while(u!=0);
        if(maxk<clauses[i].size()) maxk=clauses[i].size();
        if(mink>clauses[i].size()) mink=clauses[i].size();
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
    mpz_t is a integer type without size limitation.
    mpz_init(x) initialize x and set it to zero.
    mpz_clear(x) free the space that x uses.
    mpz_ui_pow_ui(x,b,e) calculates x=b^e. b,e are unsigned ints.
    mpz_add_ui(x,y,n) calculates x=y+n. x,y are mpz_t and n are unsigned int.
    */
    
    //calculate s=(2(k-1)/k)^n
    mpf_t s;
    mpf_init(s);
    mpf_set_ui(s,2*(maxk-1));
    mpf_div_ui(s,s,maxk);
    mpf_pow_ui(s,s,n);
    
    //calculate t=ceil(s/nbprocs)
    mpf_t t_float;
    mpf_init(t_float);
    mpf_div_ui(t_float,s,nbprocs);
    mpf_ceil(t_float,t_float);
    
    //calculate t=(int)t_float;
    mpz_t t;
    mpz_init(t);
    mpz_set_f(t,t_float);
    
    //#ifdef LOG
        printf("c nbproc=%d\n",nbprocs);
        printf("c bflag=%d\n",bflag);
        printf("c n=%d\n",n);
        printf("c m=%d\n",m);
        printf("c maxk=%d\n",maxk);
        printf("c mink=%d\n",mink);
        printf("c b=%f\n",log2(2.0-2.0/maxk)*n);
        printf("c s=");mpf_out_str(stdout,10,40,s);printf("\n");
        printf("c t_float=");mpf_out_str(stdout,10,40,t_float);printf("\n");
        printf("c t=");mpz_out_str(stdout,10,t);printf("\n");
    //#endif

    bool global_sat=false;
    unsigned int *global_a=new unsigned int[n];
    
    //parallelization with openmp
    #pragma omp parallel for
    for(unsigned int proc=0; proc<nbprocs; proc++){
    
        #ifdef LOG
            #pragma omp critical
            {
                printf("c i am worker#%d\n",proc);
            }
        #endif
        
        //assignment
        unsigned int *a=new unsigned int[n];
        //counters
        unsigned int j,l,p,r,v;
        //literal
        int u;
        //local sat
        bool sat;
        //unlimited counter
        mpz_t i;
        //container for assignment testing
        std::vector<int> unsat_border;
        std::vector<int> unsat_remain;
        
        //schoenings algorithm
        for( mpz_init(i),sat=false ; mpz_cmp(t,i)>0 && !sat && !global_sat ; mpz_add_ui(i,i,1) ){
            
            //random assignment
            for(j=0;j<n;j++)
                a[j]=rand_r(seed+proc)%2;//we increase the pointer not the seed!
            
            #ifdef LOG
                #pragma omp critical
                {
                    printf("c worker#%d: walking randomly #",proc);
                    mpz_out_str(stdout,10,i);
                    printf("\n");
                }
            #endif
                        
            //random walk until 3n steps are done or a satisfying assignment is reached
            for(j=0; j<3*n && !sat; j++){
                
                unsat_border.clear();
                unsat_remain.clear();
                //test assignment
                for(l=0,sat=true; l<m; l++){//iter over clauses and add unsat to a container
                
                    for(p=0,sat=false; p<clauses[l].size() && !sat; p++){//iter over literals
                                                                         //until sat literal is found
                                                                         //or all literals are tested
                        u=clauses[l][p];
                        sat=(u>0 ^ a[abs(u)-1]==0);
                    }
                    
                    if(!sat)//add unsat clause to a container dependent to its size
                    {
                        if(bflag){
                            if(clauses[l].size()==maxk) unsat_border.push_back(l);
                            else unsat_remain.push_back(l);
                        }else{
                            if(clauses[l].size()==mink) unsat_border.push_back(l);
                            else unsat_remain.push_back(l);
                        }
                    }
                    
                }
                sat = unsat_border.empty() && unsat_remain.empty();
                if(!sat){
                    std::vector<int> *list;
                    if(unsat_border.size()>0) list = &unsat_border;
                    else list = &unsat_remain;
                    l = list->at(rand_r(seed+proc)%list->size());
                }
                
                #ifdef LOG
                    //print assignment
                    #pragma omp critical
                    {
                        printf("c worker#%d: ",proc);
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
                            printf("c worker#%d: choosing clause #%d=(",proc,l);
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
            for(j=0;j<n;j++) global_a[j]=a[j];
        }
    }
    
    if(global_sat){
        printf("formula is satisfiable with ");
        for(int i=0;i<n;i++) printf("%d",global_a[i]);
        printf("\n");
    }else{
        printf("(with very big probability) formula is not satisfiable\n");
    }
    
}
