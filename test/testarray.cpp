#include <stdio.h>
#include <vector>

int *a;

int b[1000];

std::vector<int> v;

std::vector<int> w(1000);

int geta(int index) {
    return a[index];
}

int getb(int index) {
    return b[index];
}

int getv(int index) {
    return v[index];
}

int getw(int index) {
    return w[index];
}

int main() {

    a = new int[1000];
    
    for (int i=0; i<1000; i++) {
        a[i] = i;
        b[i] = i;
        v.push_back(i);
        w[i] = i;
    }
    
    
    return getb(100);

}