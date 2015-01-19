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
    unsigned int *seed = new unsigned int[nbprocs];
    seed[0]=time(NULL);

    int opt;
    while ((opt=getopt(argc,argv,"b:p:s:")) != -1)
    {
        switch(opt){
            case 'b':
                bflag = true;
                break;
            case 'p':
                nbprocs = atoi(optarg);
                break;
            case 's':
                seed[0] = atoi(optarg);
                break;
            case '?':
                if (optopt == 'c')
                    fprintf (stderr,"Option -%c requires an argument.\n",optopt);
                else if (isprint (optopt))
                    fprintf(stderr,"Unknown option `-%c'.\n",optopt);
                else
                    fprintf(stderr,"Unknown option character `\\x%x'.\n",optopt);
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
    
    //seeds for the remaining processes
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
    mpz_t steps;
    mpz_init(steps);
    
    //parallelization with openmp
    #pragma omp parallel for
    for(unsigned int proc=0; proc<nbprocs; proc++){
    
        #ifdef LOG
            #pragma omp critical
            printf("c worker#%d says hello\n",proc);
        #endif
        
        //assignment
        unsigned int *a=new unsigned int[n];
        //counters
        unsigned int j,l,p,r,v;
        //literal
        int u;
        //local sat
        bool clause_sat,sat;
        //unlimited counter
        mpz_t i;
        //container for assignment testing
        std::vector<int> unsat_border;
        std::vector<int> unsat_remain;
        
        //schoenings algorithm
        for( mpz_init(i),sat=false ; mpz_cmp(t,i)>0 && !sat && !global_sat ; mpz_add_ui(i,i,1) ){
                                                                 //i starts with 0 and is incremented by 1 in each iteration
                                                                 //while its lower than t or the formula is satisfied by a
            
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
                for(l=0;l<m;l++){//iter over clauses and add unsat to a container
                
                    clause_sat=false;
                
                    for(p=0; p<clauses[l].size() && !clause_sat; p++){//iter over literals
                                                                      //until sat literal is found
                                                                      //or all literals are tested
                        u=clauses[l][p];
                        clause_sat = (u>0 ^ (a[abs(u)-1] == 0));
                    }
                    
                    if(!clause_sat)
                        if(clauses[l].size()==(bflag ? maxk : mink))
                            unsat_border.push_back(l);
                        else
                            unsat_remain.push_back(l);
                    
                }
                
                #ifdef LOG
                    #pragma omp critical
                    {
                        printf("c worker#%d: unsat_border: ",proc);
                        for(p=0;p<unsat_border.size();p++)
                            printf("%d ",unsat_border[p]);
                        printf("\nc worker#%d: unsat_remain: ",proc);
                        for(p=0;p<unsat_remain.size();p++)
                            printf("%d ",unsat_remain[p]);
                        printf("\n");
                    }
                #endif
                
                //formula is satisfied if there are no unsatisfied clauses
                sat = unsat_border.empty() && unsat_remain.empty();
                
                #ifdef LOG
                    //print assignment
                    #pragma omp critical
                    {
                        printf("c worker#%d: ",proc);
                        for(p=0;p<n;p++) printf("%d",a[p]);
                        printf(sat?" satisfies ! ! ! ! ! ! ! ! ! ! ! !\n":" satisfies not\n");
                    }
                #endif
                
                if(!sat){
                    
                    //now choose a unsatisfied clause randomly, but clauses from border are prefered
                    std::vector<int> *list;
                    if(unsat_border.size()>0) list = &unsat_border;
                    else list = &unsat_remain;
                    l = list->at(rand_r(seed+proc)%list->size());
                
                    //doing a step in random walk (flipping the assignment for a variable)
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
            //you are the first, now inform the other processes
            global_sat=true;
            #pragma omp critical
            {
                //save the satisfying assignment
                for(j=0;j<n;j++)
                    global_a[j]=a[j];
            }
        }
        
        #pragma omp critical
        {
            //sum up the number of local changes
            mpz_add(steps,steps,i);
        }
    }
    
    printf("c steps=");
    mpz_mul_ui(steps,steps,3*n);
    mpz_out_str(stdout,10,steps);
    printf("\n");
    
    if(global_sat){
        printf("s SATISFIABLE\nv ");
        for(int i=0;i<n;i++)
        {
            printf("%d",global_a[i] ? i+1 : -(i+1));
            if(i<n-1) printf(" ");
            else printf("\n");
        }
    }else{
        printf("s UNSATISFIABLE\n");
    }
    
}
