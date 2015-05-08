#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_K 10

int main(int argc, char **argv) {

    bool show_table = false;

    //read commandline params
    int opt;
    while((opt=getopt(argc,argv,"t")) != -1){
        switch(opt){
        case 't': show_table = true; break;
        default:
            fprintf(stderr,"Usage: %s [options]\n\n",argv[0]);
            fprintf(stderr,"Options:\n");
            fprintf(stderr," -t    Show table.\n");
            exit(0);
        }
    }

    //read from file or from stdin
    FILE *fp;
    if(optind < argc)
    {
        fp = fopen(argv[1],"r");
    }else{
        fp = stdin;
    }

    //skip comments
    int c;
    while ((c = fgetc(fp)) == 'c')
        while (fgetc(fp) != '\n') {}

    //parse formula
    if (c == 'p')
    {
        int n;
        int m;
        int u;
        int p=0;
        int c[MAX_K+1]={0};
        int csum=0;

        if (fscanf(fp," cnf %d %d\n",&n,&m)!=2)
        {
            fprintf(stderr,"Error: Can not read header.\n");
            exit(0);
        }

        int* nbvar = new int[n]; memset(nbvar,0,n*sizeof(int));
        int* nbneg = new int[n]; memset(nbneg,0,n*sizeof(int));

        while (fscanf(fp,"%d",&u) != EOF)
        {
            if (u==0)
            {
                c[p>MAX_K ? MAX_K : p]++;
                csum++;
                p=0;
            }else{
                p++;
                if(u>0) nbvar[u-1]++;
                else nbneg[-u-1]++;
            }
        }

        printf("number of clauses: %d\n",csum);
        if(c[0]>0) printf("number of empty clauses: %d\n",c[0]);
        if(c[1]>0) printf("number of unit clauses: %d\n",c[1]);
        for(int i=2; i<MAX_K; i++)
        {
            if(c[i]>0) printf("number of %d-clauses: %d\n",i,c[i]);
        }
        if(c[MAX_K]>0) printf("number of >=%d-clauses: %d\n",MAX_K,c[MAX_K]);

        if(show_table)
        {
            printf("\n");
            printf("   Var          +          -\n");
            printf("============================\n");
            int sumvar=0,sumneg=0;
            for (int i=0; i<n; i++) {
                printf("%6d %10d %10d\n",i+1,nbvar[i],nbneg[i]);
                sumvar += nbvar[i];
                sumneg += nbneg[i];
            }
            printf("============================\n");
            printf("   Sum %10d %10d\n",sumvar,sumneg);
        }

    }

    return 0;
}
