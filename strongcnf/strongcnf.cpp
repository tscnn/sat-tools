#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int baseformula[40][3]={
	{1,2,9},		{5,6,7},		{3,4,10},		{3,9,12},	
	{-3,-8,-11},	{-1,-5,-10},	{1,6,-11},		{-1,7,11},
	{-2,-5,9},		{2,8,-9},		{1,-3,-5},		{-8,-10,11},
	{-2,-8,10},		{3,5,-9},		{-1,-9,12},		{-2,-3,-6},
	{2,10,11},		{-2,-4,-5},		{-8,-9,-12},	{4,-7,9},
	{3,5,-8},		{-5,8,10},		{-4,-6,7},		{6,-7,-12},
	{-4,5,-7},		{-6,8,-12},		{2,-6,12},		{8,11,12},
	{-7,-9,-10},	{6,7,8},		{-4,-6,-11},	{-1,-7,-12},
	{7,-10,11},		{4,9,-12},		{2,-4,12},		{-3,10,-11},
	{-1,3,-10},		{-2,4,-11},		{1,4,5},		{1,-3,6}};

//                       1       5       9
bool baseassignment[12]={1,0,0,1,1,0,0,1,1,1,0,0};

int main(int argc, char **argv){
	char c;
	int n,m;
	unsigned int seed;
	bool nset=false,mset=false,sset=false,u=false,x=false;
	while((c=getopt(argc,argv,"n:m:s:ux"))!=-1){
		switch(c){
        case 'n':
            n=atoi(optarg);
            nset=true;
            break;
        case 'm':
            m=atoi(optarg);
            mset=true;
            break;
        case 's':
            seed=atoi(optarg);
            sset=true;
            break;
        case 'u':
            u=true;
            break;
        case 'x':
            x=true;
            break;
        }
    }
    if(!nset || !mset || n%12!=0 || m%40!=0){
    	printf("strongcnf generates a partly random 3-SAT formula with only one satisfying\n");
    	printf("assignment, if the ratio m/n is good.\n");
    	printf("tsc@mailbox.org\n");
    	printf("usage: strongcnf -n NBVARIBLES -m NBCLAUSES [-s SEED] [-u]\n");
    	printf("-n NBVARIBLES   Number of variables. Must be greater than 0 and divisible by 12.\n");
    	printf("-m NBCLAUSES    Number of clauses. Must be greater than 0 and divisible by 40.\n");
        printf("-s SEED         Seed for random numbers. (optional)\n");
        printf("-u              Shuffle the literals in clauses.\n");
    }else{
	    if(!sset) seed=time(NULL);
	    int N=n/12,M=m/40,i,j,k,l,r,tmp,*tmpc,fl=0;
	    printf("c generated by strongcnf\n");
	    printf("c m/n=%f\n",(float(m)/float(n)));
	    //allocate memory
	    int **formula=new int*[m];
	    for(i=0;i<m;i++)
		    formula[i]=new int[3];
	    int **columns=new int*[3];
	    for(i=0;i<3;i++)
		    columns[i]=new int[N];
	    //fill each column incremental
	    for(i=0;i<3;i++)
		    for(j=0;j<N;j++)
			    columns[i][j]=j;
	    //start the construction of the formula
	    for(i=0;i<40;i++) //iterate all clauses of the baseformula
		    for(j=0;j<M;j++){
			    if(j%N==0)
			        //then shuffle the three columns
				    for(k=0;k<3;k++)
					    for(l=0;l<N;l++){
						    r=rand_r(&seed)%N;
						    tmp=columns[k][l];
						    columns[k][l]=columns[k][r];
						    columns[k][r]=tmp;
					    }
			    //fill the next clause of targetformula
			    for(k=0;k<3;k++){
				    int literal=baseformula[i][k];
				    int sign=literal<0?-1:1;
				    formula[i*M+j][k]=literal+12*sign*columns[k][j%N];
			    }
			    if(baseassignment[abs(baseformula[i][0])-1] == baseformula[i][0]>0 &&
			       baseassignment[abs(baseformula[i][1])-1] == baseformula[i][1]>0 &&
			       baseassignment[abs(baseformula[i][2])-1] == baseformula[i][2]>0)
			    {
			        r=rand_r(&seed)%3;
			        formula[i*M+j][r] *= -1;
			        fl++;
			    }
		    }
	    //shuffle formula
	    for(i=0;i<m;i++){
		    r=rand_r(&seed)%m;
		    tmpc=formula[i];
		    formula[i]=formula[r];
		    formula[r]=tmpc;             
	    }
        //shuffle clauses
        if(u){
            for(i=0;i<m;i++){
                for(j=0;j<3;j++){
                    r=rand_r(&seed)%3;
                    tmp=formula[i][j];
                    formula[i][j]=formula[i][r];
                    formula[i][r]=tmp;
                }             
            }
        }
	    //print the formula to stdout
	    printf("c %d forced unsat literals\n",fl);
	    printf("p cnf %d %d\n",n,m);
	    for(i=0;i<m;i++)
		    printf("%d %d %d 0\n",formula[i][0],formula[i][1],formula[i][2]);
	    //free memory
	    for(i=0;i<3;i++)
		    delete[] columns[i];
	    delete[] columns;
	    for(i=0;i<m;i++)
		    delete[] formula[i];
	    delete[] formula;
	}
	return 0;
}
