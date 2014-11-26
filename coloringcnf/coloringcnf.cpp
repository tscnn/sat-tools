/*
    //create 3-colored graph instance and reduce it without coloring to 3-SAT.
     A1         B1         C1
     A2         B2         C2
     
     für jeden Knoten i (Beispiel i=A1):
     A1_is_1   A1_is_2   A1_is_3
     
     für jede Kante ij (Beispiel ij=A1B1):
     A1_is_1 => not B1_is_1
     A1_is_2 => not B1_is_2
     A1_is_3 => not B1_is_3
     
     a => b  <=>  not a or b
     a => not b  <=>  not a or not b
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int n = 0;
    double d = 0.5;
    int opt;
    while((opt=getopt(argc,argv,"n:d:")) != -1){
        switch(opt){
        case 'n': n=atoi(optarg); break;
        case 'd': d=atof(optarg); break;
        default:
            fprintf(stderr,"Usage: %s ... \n",argv[0]);
            exit(0);
        }
    }
    int e = (int)(d*n+0.5);
    printf("c A 3-SAT formula reduced from an instance for 3-COLORING.\n");
    printf("c Construction parameters: n=%d, d=%f\n",n,d);
    printf("p cnf %d %d\n",3*n,3*n*e);
    //iterate vertices, color of a vertice i is i%3
    for(int i=0; i<n; i++){
        
        int x1 = 3*i;
        int x2 = 3*i+1;
        int x3 = 3*i+2;
        printf("%d %d %d\n",x1,x2,x3);
    }
}


double random_unique_numbers(int s, int e){

}
     