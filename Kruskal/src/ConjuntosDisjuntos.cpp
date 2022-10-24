#include "ConjuntosDisjuntos.h"
#include <assert.h>

ConjuntosDisjuntos::ConjuntosDisjuntos(int n){
    p = new int[n+1];
    for(int i=0; i <= n; i++)
        p[i] = -1;
    contar = n;
}

void ConjuntosDisjuntos::Union(int i, int j){
    //assert (p[i] < 0 && p[j] < 0);
    int temp = p[i] + p[j];
    if(p[i] > p[j]){
        p[i] = j;
        p[j] = temp;
    }else{
        p[j] = i;
        p[i] = temp;
    }
    contar--;
}

int ConjuntosDisjuntos::Find(int i){
    int r = i,temp;
    while (p[r] >= 0)
        r = p[r];
    while (i != r){
        temp = p[i];
        p[i] = r;
        i = temp;
    }
    return r;
}

int ConjuntosDisjuntos::Count(){
    return contar;
}

bool ConjuntosDisjuntos::Connected (int i, int j){
    return Find(i) == Find(j);
}

ConjuntosDisjuntos::~ConjuntosDisjuntos(){
    delete []p;
}

