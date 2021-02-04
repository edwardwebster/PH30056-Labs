//
// Created by Edward Webster on 06/02/2021.
//

#ifndef EXERCISE2_SYSTEMCLASS_H
#define EXERCISE2_SYSTEMCLASS_H

#include "Window.h"
#include "Particle.h"
#include "rnd.h"

class systemClass {
public:
    Window *window;   // pointer to the window

    rnd rgen;

    Particle *currentParticle;

    double pSize;  // particle size

    // constructor
    systemClass(Window *target_window);

    void drawSystem();

    void createParticle();

    void removeParticle();

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    void getNborPosition(double nPos[], double pos[], int index, double dist);

    void moveRandom();
};

#endif //EXERCISE2_SYSTEMCLASS_H
