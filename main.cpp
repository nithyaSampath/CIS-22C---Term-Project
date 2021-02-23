
#include <iostream>
#include "DisjointSets.hpp"
#include "Room.hpp"
#include <cstdlib>
#include <fstream>
#include "Queue.hpp"
#include "Stack.hpp"
#include "Maze.hpp"
#include <map>
#include <vector>
#include <GLUT/glut.h>

// Global variables for computer graphics
int w = 15;
int h = 15;
int doorWidth = 2;
int openGLWindowSizeX = 1024;
int openGLWindowSizeY = 800;
int innerBoxWidth = 4;
int gSizeRow = 0;
int northArray[24000];
int southArray[24000];
int eastArray[24000];
int westArray[24000];
int isPathArray[24000];
// Computer graphic functions
void drawRoom(int x, int y, int north, int south, int east, int west, int isPath);
int initOpenGL(int argc,  char** argv);
void display(void);
void reshape(int, int);

using namespace std;
int main(int argc, char * argv[]) {
    
    srand (int(time(NULL)));// random
    int sizeOfRow = 0;
    int totalRooms = 0;
    Maze maze = NULL;
    
    if (argc == 2)
    {
        maze = Maze(argv[1]);
    }
    else {  // If not reading from file
        cout << "Please enter the number of rows of the maze:" << endl;
        cin >> sizeOfRow;
        while (sizeOfRow <= 1) // Error message
        {
            cout << "The number you enter is invalid. Please enter a value larger than 1:" << endl;
            cin >> sizeOfRow;
        }
        
        totalRooms = sizeOfRow * sizeOfRow;
        maze = Maze(totalRooms);
        maze.generateRandomMaze();
    }
    
    maze.printMaze();
    
    map<int,bool> path = maze.findPathBFS();
    maze.printPath(path);
    
    path = maze.findPathDFS();
    maze.printPath(path);
    
    gSizeRow = maze.getRowSize();
    
    vector<Room*> rooms = maze.getRooms();
    for(int i=0;i<gSizeRow*gSizeRow;i++){
        northArray[i]=rooms[i]->getNorth();
        southArray[i]=rooms[i]->getSouth();
        eastArray[i]=rooms[i]->getEast();
        westArray[i]=rooms[i]->getWest();
        if(path.count(i)!=0 && path.at(i)==true){
            isPathArray[i]=1;
        }else{
            isPathArray[i]=0;
        }
    }
    
    initOpenGL(argc, argv);
    
    return 0;
}

//**************************************************
// The following functions will produce an output
// using computer graphs without animation.
//**************************************************

int initOpenGL(int argc,  char** argv)
{
    glutInit(&argc, argv);
    
    // set the window size to 1024 x 1024
    glutInitWindowSize(openGLWindowSizeX, openGLWindowSizeY);
    
    /* set the display mode to Red, Green, Blue and Alpha
     allocate a depth buffer
     enable double buffering
     */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    /* create the window */
    glutCreateWindow("Maze");
    
    /* set the glut display callback function
     this is the function GLUT will call every time
     the window needs to be drawn
     */
    glutDisplayFunc(display);
    
    /* set the glut reshape callback function
     this is the function GLUT will call whenever
     the window is resized, including when it is
     first created
     */
    glutReshapeFunc(reshape);
    
    /* set the default background color to black */
    glClearColor(0,0,0,1);
    
    /* enter the main event loop so that GLUT can process
     all of the window event messages
     */
    glutMainLoop();
    
    return 0;
}

void drawRoom(int x, int y, int north, int south, int east, int west, int isPath)
{
    
    if(north) {
        
        glBegin(GL_POLYGON);
        
        glVertex2f(x, y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y-doorWidth);
        glVertex2f(x, y-doorWidth);
        
        glEnd();
    }
    
    if(south) {
        
        glBegin(GL_POLYGON);
        
        glVertex2f(x, y-h);
        glVertex2f(x+w, y-h);
        glVertex2f(x+w, y-h+doorWidth);
        glVertex2f(x, y-h+doorWidth);
        
        glEnd();
    }
    
    if(east) {
        
        glBegin(GL_POLYGON);
        
        glVertex2f(x+w, y);
        glVertex2f(x+w, y-h);
        glVertex2f(x+w-doorWidth, y-h);
        glVertex2f(x+w-doorWidth, y);
        
        glEnd();
    }
    
    if(west) {
        
        glBegin(GL_POLYGON);
        
        glVertex2f(x, y);
        glVertex2f(x+doorWidth, y);
        glVertex2f(x+doorWidth, y-h);
        glVertex2f(x, y-h);
        
        glEnd();
    }
    
    if(isPath) {
        
        glColor3f(1, 0, 0);
        
        glBegin(GL_POLYGON);
        
        glVertex2f(x+innerBoxWidth, y-innerBoxWidth);
        glVertex2f(x+w-innerBoxWidth, y-innerBoxWidth);
        glVertex2f(x+w-innerBoxWidth, y-h+innerBoxWidth);
        glVertex2f(x+innerBoxWidth, y-h+innerBoxWidth);
        
        glEnd();
        
        glColor3f(1, 1, 1);
    }
}
void display() {
    
    /* clear the color buffer (resets everything to black) */
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* set the current drawing color to white */
    glColor3f(1, 1, 1);
    
    int tempTotal = 0;
    
    
    for(int i=0; i< gSizeRow; i++) {
        
        for(int j=0; j<gSizeRow; j++) {
            
            drawRoom(j*w, 800-(i*h), northArray[tempTotal],  southArray[tempTotal],  eastArray[tempTotal],  westArray[tempTotal], isPathArray[tempTotal]);
            tempTotal++;
        }
    }
    
    glutSwapBuffers();
}

/*! glut reshape callback function.  GLUT calls this function whenever
 the window is resized, including the first time it is created.
 You can use variables to keep track the current window size.
 */
void reshape(int width, int height)
{
    /* tell OpenGL we want to display in a recangle that is the
     same size as the window
     */
    glViewport(0,0,width,height);
    
    /* switch to the projection matrix */
    glMatrixMode(GL_PROJECTION);
    
    /* clear the projection matrix */
    glLoadIdentity();
    
    /* set the camera view, orthographic projection in 2D */
    gluOrtho2D(0,width,0,height);
    
    /* switch back to the model view matrix */
    glMatrixMode(GL_MODELVIEW);
}
