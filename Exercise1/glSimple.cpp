#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
// glTest.cpp : Defines the entry point for the console application.
//

#include <GLUT/glut.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
using namespace std;

// functions which are needed for openGL go into a namespace so that we can identify them
namespace drawFuncs {
    void handleKeypress(unsigned char key, int x, int y);

    void display();

    void update(int val);

    void introMessage();

    float position = 0;
}

// set up some colours for use when drawing stuff
namespace colours {
    GLfloat blue[] = {0.1, 0.3, 0.9, 1.0};   // blue
    GLfloat red[] = {1.0, 0.2, 0.1, 0.2};   // red
}

// class for the window
class Window {
public:
    string title;
    int size[2];
    int pos[2];

    void locateOnScreen() {
        // the fx sets where on the screen the window will appear
        // (values should be between 0 and 1)
        double fx[] = {0.7, 0.5};
        pos[0] = (glutGet(GLUT_SCREEN_WIDTH) - size[0]) * fx[0];
        pos[1] = (glutGet(GLUT_SCREEN_HEIGHT) - size[1]) * fx[1];
    }

    // constructor, size is in pixels
    Window(int set_size[], string &set_title);

    // function which prints a string to the screen, at a given position, with a given color
    // note position is "absolute", not easy to get two strings spaced one above each other like this
    //    (also position is for start of string, measured up and right from window centre)
    void displayString(ostringstream &str, double x, double y, GLfloat col[]);

};

Window *mainWindow;  // global !


// this is the MAIN program
int main(int argc, char **argv) {
    // turn on glut (needed for graphics)
    glutInit(&argc, argv);

    int window_size[] = {480, 480};
    string window_title("Open GL Demo");

    // this creates the window (note mainWindow is a global variable (pointer))
    mainWindow = new Window(window_size, window_title);

    drawFuncs::introMessage();

    // tell openGL how to redraw the screen and respond to the keyboard
    glutDisplayFunc(drawFuncs::display);
    glutKeyboardFunc(drawFuncs::handleKeypress);

    // pass control to openGL
    glutMainLoop();


    // NOTE: the program never gets to this point,
    // the glutMainLoop function never ends unless we exit the whole program, eg by using exit(0)
    cin.get();
    return 0;
}

// this function gets executed when the program starts
void drawFuncs::introMessage() {
    cout << "Hi there" << endl;
    cout << "Press q or e in the openGL window to exit" << endl;
}

// this gets executed when the user hits a key
void drawFuncs::handleKeypress(unsigned char key, int x, int y) {
    // this "switch" looks at which key was pressed
    // if editing, don't forget to put a break after each case.

    switch (key) {
        case 'q':
        case 'e':
            cout << "Exiting..." << endl;
            exit(0);
            break;
        case 'u':
            position += 0.05;
            update(position);
            cout << "Updating View " << position << endl;
            break;
        default:
            break;
    }
}

void drawFuncs::update(int val) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1.0,   /* camera position */
              0.0, 0.0, -1.0,        /* point to look at */
              0.0, 1.0, 0.0);

    ostringstream updateString;
    updateString << "Hello World";
    mainWindow->displayString(updateString, val, -val, colours::blue);
    glutSwapBuffers();
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
    ostringstream str;
    str << "a string";
    // note: 0 , 0.3 set the location to print the string (relative to centre of window)
    mainWindow->displayString(str, 0.0, 0.3, colours::red);

    //  Swap contents of backward and forward frame buffers
    glutSwapBuffers();
}


// Window constructor
Window::Window(int set_size[], string &set_title) {
    size[0] = set_size[0];
    size[1] = set_size[1];
    title = set_title;

    locateOnScreen();
    glutInitWindowSize(size[0], size[1]);
    glutInitWindowPosition(pos[0], pos[1]);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(title.c_str());

    // sets the background to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

// within the Window class, print a string at a given position, don't worry about how this works...
void Window::displayString(ostringstream &str, double x, double y, GLfloat col[]) {
    string localString = str.str();
    glColor4fv(col);
    glRasterPos2d(x, y);
    for (int i = 0; i < localString.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, localString[i]);
    }
}
