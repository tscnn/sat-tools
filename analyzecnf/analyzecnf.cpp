#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    
    //read from file or from stdin
    FILE *fp;
    if (argc >= 2) {
        fp = fopen(argv[1],"r");
    } else {
        fp = stdin;
    }
    
    //skip comments
    int c;
    while ((c = fgetc(fp)) == 'c')
        while (fgetc(fp) != '\n') {}
    
    //parse formula
    if (c == 'p') {
        int n,m,l,clause[3],p=0,ic=0,c=0;
        if (fscanf(fp," cnf %d %d\n",&n,&m)!=2) {
            printf("cannot read input");
            return 0;
        }
        int* nbvar = new int[n]; memset(nbvar,0,n*sizeof(int));
        int* nbneg = new int[n]; memset(nbneg,0,n*sizeof(int));
        while (fscanf(fp,"%d",&l) != EOF) {
            if (l == 0) {
                c++;
                if (clause[0]==clause[1] || -clause[0]==clause[1] || 
                    clause[1]==clause[2] || -clause[1]==clause[2] ||
                    clause[0]==clause[2] || -clause[0]==clause[2] || p!=3)
                {
                    ic++; //illegal clause found
                }
                p = 0;
            } else {
                clause[p] = l;
                p++;
                if (l > 0) {
                    nbvar[l-1]++;
                } else {
                    nbneg[-l-1]++;
                }
            }
        }
        printf("\n");
        printf("number of clauses: %d\n",c);
        printf("number of illegal clauses: %d\n",ic);
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
    
    return 0;
}
