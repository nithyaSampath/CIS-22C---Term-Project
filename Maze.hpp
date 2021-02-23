// Specification of Maze class
// Written By: Camila Picanco Mesquita, Dixon Dai, Nithyasree Sampath and Natalia Mendonca
#ifndef Maze_hpp
#define Maze_hpp

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "Room.hpp"
#include "Queue.hpp"
class Maze{
    
private:
    vector<Room *> rooms;
    int totalRooms;
    int rowSize;
    
public:
    Maze(int totalSize);
    Maze(string filename);
    int getRowSize() {return rowSize;}
    void printMaze();
    vector<Room*> getRooms() const {return rooms;}
    void generateRandomMaze();
    int getRandomRoom();
    map<int,bool> findPathBFS();
    map<int,bool> findPathDFS();
    void printPath(map<int,bool> path);
    void clearVisitedRooms();
};


#endif
