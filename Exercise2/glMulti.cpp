// glTest.cpp : Defines the entry point for the console application.
//

#include <GLUT/glut.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include "Window.h"
#include "systemClass.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
using namespace std;

// functions which are needed for openGL go into a namespace so that we can identify them
namespace drawFuncs {
    void handleKeypress(unsigned char key, int x, int y);

    void display();

    void update(int val);

    void introMessage();
}

systemClass *simulation;
ofstream logfile;
ofstream positionfile;

int main(int argc, char **argv) {

    // Create logfile
    logfile.open("dla.log");
    positionfile.open("output.csv");

    // Initialize GLUT
    glutInit(&argc, argv);

    int window_size[] = {500, 500};
    string window_title("Open GL Particle System");

    // Create the Window
    Window *main_window;
    main_window = new Window(window_size, window_title);
    // Create system targeting 'main_window'
    simulation = new systemClass(main_window);

    drawFuncs::introMessage();

    // tell openGL how to redraw the screen and respond to the keyboard
    glutDisplayFunc(drawFuncs::display);
    glutKeyboardFunc(drawFuncs::handleKeypress);
    glutTimerFunc(10, drawFuncs::update, 0);
    glutMainLoop(); // pass control to openGL

    return 0;
}

// this function gets executed when the program starts
void drawFuncs::introMessage() {
    cout << "OpenGL Particle Simulation System by Edward Webster" << endl;
    cout << "DLA (Diffusion Limited Aggregation) Simulation" << endl;
    cout << "Press q or e in the main window to exit" << endl;

    printf("Press \'c\' to add a seed particle at the origin\n");
    printf("Press \'d\' to remove the current seed\n");
}

void drawFuncs::handleKeypress(unsigned char key, int x, int y) {

    // switch for keypresses
    logfile << key << " pressed" << endl;

    switch (key) {
        case 'q':
        case 'e':
            cout << "Exiting..." << endl;
            logfile.close();
            positionfile.close();
            exit(0);
            break;
        case 'c':
            printf("Seed particle created\n");
            simulation->createParticle();
            break;
        case 'd':
            printf("Current seed particle removed\n");
            simulation->removeParticle();
            break;
        case 'l':
            simulation->moveLeft();
            break;
        case 'j':
            simulation->moveRight();
            break;
        case 'i':
            simulation->moveUp();
            break;
        case 'k':
            simulation->moveDown();
            break;
        case 'u':
            printf("Update\n");
            simulation->moveRandom();
            break;
    }
    glutPostRedisplay();
}

// this function redraws the window when necessary
void drawFuncs::display() {
    //  Clear the window (or more specifically the frame buffer)...
    //  This happens by replacing all the contents of the frame
    //  buffer by the clear color (black in our case)
    glClear(GL_COLOR_BUFFER_BIT);

    // this puts the camera at the origin (not sure why) with (I think) z axis out of page and y axis up
    // there is also the question of the GL perspective which is not set up in any clear way at the moment
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1.0,   /* camera position */
              0.0, 0.0, -1.0,        /* point to look at */
              0.0, 1.0, 0.0);            /* up direction */

    // at this point we can draw stuff, eg a string
    simulation->drawSystem();

    //  Swap contents of backward and forward frame buffers
    glutSwapBuffers();
}

void drawFuncs::update(int val) {
    simulation->moveRandom();

    positionfile << simulation->currentParticle->pos[0] << ", " << simulation->currentParticle->pos[1] << endl;

    glutPostRedisplay();

    int wait = 100;
    glutTimerFunc(wait, update, 0);
}

#pragma clang diagnostic pop