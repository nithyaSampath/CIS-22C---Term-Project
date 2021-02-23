// Implementation of Maze class
// Written By: Camila Picanco Mesquita, Dixon Dai, Nithyasree Sampath and Natalia Mendonca

#include "Maze.hpp"
#include <map>
#include <vector>
#include <math.h>
#include <fstream>
#include "DisjointSets.hpp"
#include "Stack.hpp"

Maze::Maze(int totalRooms)
{
    this->totalRooms = totalRooms;
    rowSize = sqrt(totalRooms);
    
    for(int i=0; i< totalRooms; i++)
    {
        // create Room objects
        rooms.push_back(new Room(i, rowSize));
    }
}

Maze::Maze(string filename)
{
    ifstream mazeFile(filename);
    
    if(mazeFile.is_open()) {
        
        // read first line as size of row
        mazeFile >> rowSize;
        // get total rooms
        totalRooms = rowSize * rowSize;
        
        for(int i = 0; i < totalRooms; i++) {
            // create Room objects
            rooms.push_back(new Room(i, rowSize));
        }
        int north = 0, south = 0, east = 0, west = 0;
        
        for(int i = 0; i < totalRooms; i++) {
            //cout << i << " " << north << "  "  << south <<  "  " << east << "  " << west << endl;
            mazeFile >> north >> south >> east >> west ;
            
            rooms[i]->setNorth(north);
            rooms[i]->setSouth(south);
            rooms[i]->setEast(east);
            rooms[i]->setWest(west);
        }
    }
    else {
        cout << endl << "maze.txt open error." << endl;
    }
    mazeFile.close();
}

void Maze::generateRandomMaze()
{
    QuickUnionDS ds(totalRooms);
    
    //==============================================
    // build random maze
    // While (S.find(0) != S.find(N - 1))
    //    Choose randomly a pair (i, j) of adjacent rooms i and j
    //    If (S.find(i) != S.find(j))
    //       Open the doors connecting rooms i and j in the maze
    //       S.union(S.find(i), S.find(j))
    //===============================================
    while(ds.find(0) != ds.find(totalRooms-1) ) {
        
        int randomRoom = getRandomRoom();
        int randomAdjRoom = rooms[randomRoom]->getRandomAdjRoom();       // give me a random adj room
        
        // cout << "Random Room = " << randomRoom << " Random adj Room = " << randomAdjRoom << endl;
        // cout << "Root of Random Room = " << ds.find(randomRoom) << " Root of Random adj Room = " << ds.find(randomAdjRoom) << endl;
        
        if( ds.find(randomRoom) != ds.find(randomAdjRoom) ) {
            
            rooms[randomRoom]->connectRooms(randomAdjRoom);     // automatically decide which door to open
            rooms[randomAdjRoom]->connectRooms(randomRoom);
            
            ds.connect( ds.find(randomRoom) , ds.find(randomAdjRoom) ) ;
        }
    }
}

int Maze::getRandomRoom()
{
    // returns random number in range: a 0 to (totalRooms - 1)
    return (rand() % totalRooms);
}

//==============================================
// BFS
// Create an empty queue Q of room numbers
// Enqueue room number 0 to Q
// Mark room number 0 as visited
// While Q is not empty {
//    Dequeue an element from Q and store it to i
//    If i is equal to (N - 1) then break from the while-loop and print the path found
//    For each room j adjacent to room i such that there is a passage way between rooms i and j
//        and room j is not marked visited {
//            Enqueue room number j to Q
//            Mark room number j as visited
// } }
//==============================================
map<int,bool> Maze::findPathBFS()
{
    clearVisitedRooms();
    
    cout << "Rooms visited by BFS: " ;
    
    Queue <Room *> roomQueue;
    
    //Enqueue room number 0 to Q
    roomQueue.insert(rooms[0]);
    map<int,int> previous;
    
    while(!roomQueue.isEmpty()) {
        
        Room *roomI = roomQueue.remove();
        rooms[roomI->getRoomId()]->setVisited(1);
        
        cout << " " << roomI->getRoomId();
        
        if(roomI->getRoomId() == totalRooms-1) break;
        
        // check all 4 adjecent rooms
        for(int i=0; i<4; i++) {
            // get the id of adjecent room if it is connected
            int adjRoom = roomI->getAdjacentRoomIfConnected(i);
            if(adjRoom != -1 && (rooms[adjRoom]->getVisited() != 1) )
            {
                roomQueue.insert(rooms[adjRoom]);
                previous[adjRoom]=roomI->getRoomId();
            }
        }
    }
    cout << endl;
    
    cout << "Path (inverse):";
    map<int,bool> path;
    int current = totalRooms-1;
    while(true){
        cout << " " << current;
        path.emplace(current, true);
        if(current == 0){
            break;
        }
        current = previous[current];
    }
    cout << endl;
    return path;
}

//==============================================
// DFS
// Create an empty stack S of room numbers
// Push room number 0 to S
// Mark room number 0 as visited
// While S is not empty {
// Pop an element from S and store it to i
//    If i is equal to (N - 1) then break from the while-loop and print the path found
//        For each room j adjacent to room i such that there is a passage way between rooms i and j
//        and room j is not marked visited {
//            Push room number j to S
//            Mark room number j as visited
//        } }
//==============================================
map<int,bool> Maze::findPathDFS()
{
    clearVisitedRooms();
    cout << "Rooms visited by DFS: " ;
    Stack <Room *> stack;
    
    stack.insert(rooms[0]);
    map<int,int> previous;
    
    while(!stack.isEmpty()) {
        
        Room *newRoomI = stack.remove();
        newRoomI->setVisited(1);
        
        cout << " " << newRoomI->getRoomId();
        
        if(newRoomI->getRoomId() == totalRooms-1) break;
        
        //checking adjacent rooms in inverse order,
        //since the stack will invert it again when we visit them
        for(int i=3; i>=0; i--) {
            // get the id of adjecent room if it is connected
            int adjRoom = newRoomI->getAdjacentRoomIfConnected(i);
            if(adjRoom != -1 && (rooms[adjRoom]->getVisited() != 1) )
            {
                stack.insert(rooms[adjRoom]);
                previous[adjRoom]=newRoomI->getRoomId();
            }
        }
    }
    cout << endl;
    
    cout << "Path (inverse):";
    map<int,bool> path;
    vector<int> roomsInPath;
    int current = totalRooms-1;
    while(true){
        cout << " " << current;
        path.emplace(current, true);
        if(current == 0){
            break;
        }
        current = previous[current];
    }
    cout << endl;
    
    return path;
    
}

void Maze::printPath(map<int, bool> path)
{
    cout << "Path:" << endl;
    for(int i=0; i < totalRooms; i++){
        if(path.count(i) != 0 && path.at(i)==true)
        {
            cout << " X";
        }else
        {
            cout << "  ";
        }
        if((i+1)%rowSize==0)
        {
            cout << endl;
        }
    }
    cout << endl;
    
}

void Maze::clearVisitedRooms()
{
    for(int i=0; i<totalRooms; i++){
        rooms[i]->setVisited(0);
    }
}

void Maze::printMaze()
{
    cout << " ";
    for (int c = 0; c < rowSize; c++) {
        cout << ((rooms[c]->getNorth()) ? "__" : "  ");
    }
    cout << endl;
    
    int i = 0;
    for (int r = 0; r < rowSize; r++) {
        for (int c = 0; c < rowSize; c++) {
            if (c == 0) cout << ((rooms[i]->getWest()) ? "|" : " ");
            cout << ((rooms[i]->getSouth()) ? "_" : " ");
            if (rooms[i]->getSouth() || (c < rowSize-1 && rooms[i+1]->getSouth())) {
                cout << ((rooms[i]->getEast()) ? "|" : "_");
            } else {
                cout << ((rooms[i]->getEast()) ? "|" : " ");
            }
            i++;
        }
        cout << endl;
    }
    cout << endl;
}


