// Specification of DisjointSets class
// Written By: Camila Picanco Mesquita, Dixon Dai, Nithyasree Sampath and Natalia Mendonca

#ifndef DisjointSets_hpp
#define DisjointSets_hpp
#include <iostream>
using namespace std;

template <typename T>
class QuickUnionDS {
private:
    T *id;
    int numberOfElements;
public:
    //Constructor that creates a disjoint set with one room
    QuickUnionDS() {
        numberOfElements = 1;
        id = new int[1];
        for (int i = 0; i < 1; i++){
            id[i] = i; // create disjoint set with 1 room
        }
    }
    // Freeing alocated memory
    ~QuickUnionDS()
    {
        delete [] id; // delete disjoint set
    }
    //Constructor that creates a disjoint set with N rooms
    QuickUnionDS(int N)
    {
        numberOfElements = N;
        id = new int[N];
        for (int i = 0; i < N; i++){ // create disjoint set with N rooms
            id[i] = i;
        }
    }
    //Function that finds the set that the room belongs to
    int find(int i)
    {
        if(i >= numberOfElements) // if room is greater than biggest element in disjoint set, return
            return 0;
        
        while (i != id[i]) { // if room is not equal to it's parent
            i = id[i]; //continue searching through disjoint set
        }
        return i; // return index
    }
    //Function that checks if two rooms are connected to each other
    bool isConnected(int p, int q)
    {
        return (find(p) == find(q)); //calls find function to check if rooms are connected to each other
    }
    
    //function that connects two rooms together
    void connect(int p, int q) {
        int i = find(p); // call find function to get index of each room in disjoint set
        int j = find(q);
        id[i] = j; //set parent of room p as room q
    }
    
    //function that prints each room inside the disjoint set
    void printSets() {
        for (int i = 0; i < numberOfElements; i++){
            cout << id[i] << "  "; // print each room that is inside the disjoint set
        }
        cout << endl;
    }
};
#endif
