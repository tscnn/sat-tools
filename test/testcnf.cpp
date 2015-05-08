#include <stdio.h>
#include <stdlib.h>

#include "../inc/cnf.cpp"

int main() {

    CNF f;
    f.read(stdin);
    printf("mink=%d\n",f.mink());
    printf("maxk=%d\n",f.maxk());

}