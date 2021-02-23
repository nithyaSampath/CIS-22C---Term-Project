// Implementation of DisjointSets class
// Written By: Camila Picanco Mesquita, Dixon Dai, Nithyasree Sampath and Natalia Mendonca

#include "DisjointSets.hpp"
QuickUnionDS::QuickUnionDS() {
    numberOfElements = 1;
    id = new int[1];
    for (int i = 0; i < 1; i++){
        id[i] = i;
    }
}
// Freeing alocated memory
QuickUnionDS::~QuickUnionDS()
{
    delete [] id;
}

QuickUnionDS::QuickUnionDS(int N)
{
    numberOfElements = N;
    id = new int[N];
    for (int i = 0; i < N; i++){
        id[i] = i;
    }
}

int QuickUnionDS::find(int i)
{
    if(i >= numberOfElements)
        return 0;
    
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

bool QuickUnionDS::isConnected(int p, int q)
{
    return (find(p) == find(q));
}

void QuickUnionDS::connect(int p, int q) {
    int i = find(p);
    int j = find(q);
    id[i] = j;
}

void QuickUnionDS::printSets() {
    for (int i = 0; i < numberOfElements; i++){
        cout << id[i] << "  ";
    }
    cout << endl;
}
