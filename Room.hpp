// Specification of Room class
// Written By: Camila Picanco Mesquita, Dixon Dai, Nithyasree Sampath and Natalia Mendonca
#ifndef Room_hpp
#define Room_hpp
#include <iostream>
#include <cstdlib>

using namespace std;

class Room {
private:
    int south;
    int north;
    int west;
    int east;
    int roomId;
    int sizeOfRow;
    int sizeOfGraph;
    int adjecentRooms[4];           // adjecent room ids
    int totalAdjRooms;
    int visited;
public:
    Room();
    Room(int roomNum, int sg);
    void setVisited(int value) {visited = value;}
    int getRoomId() {return roomId;}
    int getVisited() {return visited;}
    // set the north door
    void setNorth(int n);
    // set the south door
    void setSouth(int s);
    // set the east door
    void setEast(int e);
    // set the West door
    void setWest(int w);
    // getter methods
    int getSouth() {return south;}
    int getNorth() {return north;}
    int getWest() {return west;}
    int getEast() {return east;}
    int getRandomAdjRoom();
    // connect this room with adj room
    void connectRooms( int adjRoomId);
    // connect this room with adj room
    int getAdjacentRoomIfConnected( int direction);
    void printRoomInfo();
};

#endif
