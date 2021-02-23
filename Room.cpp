// Implementation of Room class
// Written By: Camila Picanco Mesquita, Dixon Dai, Nithyasree Sampath and Natalia Mendonca

#include "Room.hpp"
#include <iostream>
using namespace std;

Room::Room()
{
    south = north = west = east = 0;
    roomId = -1;
    sizeOfRow = 0;
    sizeOfGraph = 0;
}

Room::Room(int roomNum, int rowSize) {
    visited = 0;
    roomId = roomNum;
    sizeOfRow = rowSize;
    sizeOfGraph = rowSize * rowSize;
    totalAdjRooms = 0;
    // start with adj room id as -1, -1 means there is no adj room
    adjecentRooms[0] = adjecentRooms[1] = adjecentRooms[2] = adjecentRooms[3] = -1;
    
    // set the north adjecent room
    int northRoomId = roomId - rowSize;
    if(northRoomId >= 0 ){
        adjecentRooms[0] = northRoomId;
        totalAdjRooms++;
    }
    // set the south adjecent room number
    int southRoomId = roomId + rowSize;
    if(southRoomId <= sizeOfGraph - 1)
    {
        adjecentRooms[1] = southRoomId;
        totalAdjRooms++;
    }
    // set the east adjecent room number
    // for rooms on the right most will not have any east adj room
    if( ((roomId + 1) % rowSize != 0)) {
        adjecentRooms[2] = roomId + 1;
        totalAdjRooms++;
    }
    // set the west adjecent room number
    if((roomId % rowSize != 0 )){
        adjecentRooms[3] = roomId - 1;
        totalAdjRooms++;
    }
    // set all the doors as closed
    setSouth(1);
    setNorth(1);
    setEast(1);
    setWest(1);
}

// set the north door
void Room::setNorth(int n) {
    // set the north door of all top rooms
    for(int i = 0; i < sizeOfRow; i++){
        if(roomId == i)
            north = 1;
    }
    if (roomId == 0)
        north = 0;                  // open the north door of Start room
    else
        north = n;
}

// set the south door
void Room::setSouth(int s) {
    // set the south door of all the bottom rooms
    for(int i = sizeOfGraph - sizeOfRow - 1; i < sizeOfGraph; i++) {
        if(roomId == i)
            south = 1;
    }
    if(roomId == (sizeOfGraph - 1))
        south = 0;                      // open the south door for Goal room
    else
        south = s;
}

// set the east door
void Room::setEast(int e) {
    
    // set the east door of all right rooms. They are always closed
    for(int i = sizeOfRow-1; i < sizeOfGraph; i+=sizeOfRow) {
        if(roomId == i)
            east = 1;
    }
    east = e;
}

// set the West door
void Room::setWest(int w) {
    // set the west door of all right rooms. They are always closed
    for(int i = 0; i < sizeOfGraph-sizeOfRow; i+=sizeOfRow) {
        if(roomId == i)
            west = 1;
    }
    west = w;
}

int Room::getRandomAdjRoom() {
    int temp[4];
    int j = 0;
    
    // copy the adjroom values that are not -1 to temp array
    for(int i = 0; i< 4; i++) {
        if (adjecentRooms[i] != -1) {
            temp[j++] = adjecentRooms[i];
        }
    }
    return temp[rand() % totalAdjRooms] ;   // returns a random number in range : 0 to (totalAdjRooms - 1)
}

// connect this room with adj room
void Room::connectRooms( int adjRoomId) {
    
    if( adjRoomId == adjecentRooms[0] ) setNorth(0);
    if( adjRoomId == adjecentRooms[1] ) setSouth(0);
    if( adjRoomId == adjecentRooms[2] ) setEast(0);
    if( adjRoomId == adjecentRooms[3] ) setWest(0);
}

// connect this room with adj room
int Room::getAdjacentRoomIfConnected( int direction) {
    
    if( direction == 0 &&  north == 0)
        return adjecentRooms[0];
    if( direction == 1 &&  south == 0)
        return adjecentRooms[1];
    if( direction == 2 &&  east == 0)
        return adjecentRooms[2];
    if( direction == 3 &&  west == 0)
        return adjecentRooms[3];
    return -1;
}

void Room::printRoomInfo() {
    cout << "The room number is: " << roomId << endl;
    if(south == 0)
        cout << "The south door is open." << endl;
    else if (north == 0)
        cout << "The north door is open." << endl;
    else if(west == 0)
        cout << "The west door is open." << endl;
    else if(east == 0)
        cout << "The east door is open." << endl;
    else
        cout << "None of the doors are open" << endl;
    
    cout << "Adj rooms N/S/E/W: " << adjecentRooms[0] << " " << adjecentRooms[1] << " " << adjecentRooms[2] << " " << adjecentRooms[3] << endl;
}
