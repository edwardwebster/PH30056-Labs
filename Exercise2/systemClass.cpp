//
// Created by Edward Webster on 06/02/2021.
//

#include "systemClass.h"
#include "GLUT/glut.h"

namespace colours {
    GLfloat blue[] = {0.1, 0.3, 0.9, 1.0};   // blue
    GLfloat red[] = {1.0, 0.2, 0.1, 0.2};    // red
}

// Constructor with systemClass assignment
systemClass::systemClass(Window *target_window) {
    window = target_window;
    currentParticle = 0;
    pSize = 0.05;
    rgen.setSeed(0);
}

// Simulation render
void systemClass::drawSystem() {
    if (currentParticle != 0) {
        window->drawSquare(currentParticle->pos, pSize, colours::blue);
    }
}

void systemClass::createParticle() {
    if (currentParticle == 0) currentParticle = new Particle(0.0, 0.0);
}

void systemClass::removeParticle() {
    if (currentParticle != 0) {
        delete currentParticle;
        currentParticle = 0;
    }
}

void systemClass::moveLeft() {
//    assert(currentParticle!=0);
    if (currentParticle == 0) return;
    currentParticle->pos[0] += pSize;
}

void systemClass::moveRight() {
//    assert(currentParticle!=0);
    if (currentParticle == 0) return;
    currentParticle->pos[0] -= pSize;
}

void systemClass::moveUp() {
    if (currentParticle == 0) return;
    currentParticle->pos[1] += pSize;
}

void systemClass::moveDown() {
    if (currentParticle == 0) return;
    currentParticle->pos[1] -= pSize;
}

void systemClass::getNborPosition(double *nPos, double *pos, int index, double dist) {

    nPos[0] = pos[0];
    nPos[1] = pos[1];

    switch (index) {
        case 0:
            nPos[0] += dist;
            break;
        case 1:
            nPos[1] += dist;
            break;
        case 2:
            nPos[0] -= dist;
            break;
        case 3:
            nPos[1] -= dist;
            break;
    }
}

void systemClass::moveRandom() {
    if (currentParticle == 0) createParticle();

    int numberOfNbors = 4;
    int nborIndex = rgen.randomInt(numberOfNbors);

    double newPos[2];
    getNborPosition(newPos, currentParticle->pos, nborIndex, pSize);

    for (int i = 0; i < 2; i++) {
        currentParticle->pos[i] = newPos[i];
    }

}