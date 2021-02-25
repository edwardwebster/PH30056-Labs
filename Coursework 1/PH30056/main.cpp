#include <GLUT/glut.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>

#include "DLASystem.h"
#include "Window.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
using namespace std;

// functions which are needed for openGL go into a namespace so that we can identify them
namespace eventManager {
    void handleKeypress(unsigned char key, int x, int y);

    void display(void);

    void update(int val);

    void introMessage();
}

// this is a global pointer, which is how we access the system itself
DLASystem *dlaSystem;

int main(int argc, char **argv) {
    // turn on glut
    glutInit(&argc, argv);

    int window_size[] = {500, 500};
    string window_title("DLA Simulation");

    Window *window = new Window(window_size, window_title); // Create window
    dlaSystem = new DLASystem(window); // And initialized DLA System

    // this is the seed for the random numbers
    int seed = 5;
    dlaSystem->setSeed(seed);
    dlaSystem->setStickingProbability(1.0);

    // print the "help" message to the console
    eventManager::introMessage();

    // tell openGL how to redraw the screen and respond to the keyboard
    glutDisplayFunc(eventManager::display);
    glutKeyboardFunc(eventManager::handleKeypress);

    // tell openGL to do its first update after waiting 10ms
    int wait = 10;
    int val = 0;
    glutTimerFunc(wait, eventManager::update, val);

    // start the openGL stuff
    glutMainLoop();

    return 0;
}

// this is just a help message
void eventManager::introMessage() {
    cout << "Keys (while in graphics window):" << endl << "  q or e to quit (or exit)" << endl;
    cout << "  h to print this message (help)" << endl;
    cout << "  u for a single update" << endl;
    cout << "  g to start running (go)" << endl;
    cout << "  p to pause running" << endl;
    cout << "  s to run in slow-mode" << endl;
    cout << "  f to run in fast-mode" << endl;
    cout << "  r to clear everything (reset)" << endl;
    cout << "  z to pause and zoom in" << endl;
    cout << "  w or b to change background colour to white or black" << endl;
}

// openGL function deals with the keyboard
void eventManager::handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'h':
            eventManager::introMessage();
            break;
        case 'q':
        case 'e':
            cout << "Exiting..." << endl;
            // delete the system
            delete dlaSystem;
            exit(0);
            break;
        case 'p':
            cout << "pause" << endl;
            dlaSystem->pauseRunning();
            break;
        case 'g':
            cout << "go" << endl;
            dlaSystem->setRunning();
            glutTimerFunc(0, eventManager::update, 0);
            break;
        case 's':
            cout << "slow" << endl;
            dlaSystem->setSlow();
            break;
        case 'w':
            cout << "white" << endl;
            dlaSystem->setWinBackgroundWhite();
            break;
        case 'b':
            cout << "black" << endl;
            dlaSystem->setWinBackgroundBlack();
            break;
        case 'f':
            cout << "fast" << endl;
            dlaSystem->setFast();
            break;
        case 'r':
            cout << "reset" << endl;
            dlaSystem->Reset();
            break;
        case 'z':
            cout << "zoom" << endl;
            dlaSystem->pauseRunning();
            dlaSystem->viewAddCircle();
            break;
        case 'u':
            cout << "upd" << endl;
            dlaSystem->Update();
            break;
        case '0':
            cout << "current size: \t\t" << dlaSystem->getClusterSize() << endl;
            cout << "number of particles: \t" << dlaSystem->getNumberOfParticles() << endl;
            break;
    }
    // tell openGL to redraw the window
    glutPostRedisplay();
}

// this function gets called whenever the algorithm should do its update
void eventManager::update(int val) {
    int wait;  // time to wait between updates (milliseconds)

    if (dlaSystem->running) {
        if (dlaSystem->slowNotFast == 1)
            wait = 10;
        else
            wait = 0;

        dlaSystem->Update();

        // tell openGL to call this funtion again after "wait" milliseconds
        glutTimerFunc(wait, eventManager::update, 0);
    }

}

// this function redraws the window when necessary
void eventManager::display() {
    //  Clear the window or more specifically the frame buffer...
    //  This happens by replacing all the contents of the frame
    //  buffer by the clear color (black in our case)
    glClear(GL_COLOR_BUFFER_BIT);

    // this puts the camera at the origin (not sure why) with (I think) z axis out of page and y axis up
    // there is also the question of the GL perspective which is not set up in any clear way at the moment
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1.0,   /* camera position */
              0.0, 0.0, -1.0,        /* point to look at */
              0.0, 1.0, 0.0);           /* up direction */

    //dlaSystem->DrawSpheres();
    dlaSystem->DrawSquares();

    //  Swap contents of backward and forward frame buffers
    glutSwapBuffers();
}


#pragma clang diagnostic pop