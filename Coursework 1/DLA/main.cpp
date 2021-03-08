//
// Created by Edward Webster on 20/01/2021.
//
#include <iostream>
#include <fstream>
#include "randomGenerator.h"

using namespace std;

#define width 500
#define height 500
#define numberOfWalkers 5000
#define numberOfWalkerSteps 10000
#define stickingProbability 1.0
#define outputFile "../../Data/Extra/output.csv."

class walker {
public:
    int x, y;
    bool active;

    bool touchingCluster(int cluster[width][height]) {

        if (not active) return true;

        // For loop over x, y, z
        for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {


                if (x + k <= 0 || x + k >= width) return false;
                if (y + l <= 0 || y + l >= height) return false;

                // If clustered particle at position k or l
                if (cluster[x + k][y + l] == 1) {

//                    active = false;
//                    return true;

//                    double x = randomBetween(0, 1000)/1000;

                    if ( randomBetween(0, 1000)/1000 < stickingProbability ){
                        active = false;
                        return true;
                    } else {
//                        active = false;
                    }

                }

            }
        }

        return false;
    }

    void takeRandomStep() {
        // Update position by moving up, down, left or right
        if (not active) return;

        x += randomBetween(-1, 1);
        y += randomBetween(-1, 1);
        //z += randomBetween(-1, 1);

        // Cannot leave boundary
//        if (x <= 0) x++;
//        if (x >= width) x--;
//
//        if (y <= 0) y++;
//        if (y >= height) y--;

        // Periodic boundary conditions instead
        if (x <= 0) x = width - 1;
        if (x >= width) x = 1;

        if (y <= 0) y = height - 1;
        if (y >= height) y = 1;

    }

    walker() {
        x = randomBetween(0, width-1);
        y = randomBetween(0, height-1);
        active = true;
    };

    void reset() {
        x = randomBetween(0, width-1);
        y = randomBetween(0, height-1);
        active = true;
    };
};

walker particleList[numberOfWalkers];

void writeToCSV(int time, int grid[width][height]) {
    ofstream output;
    output.open(outputFile + to_string(time));

    output << "x,y,z,state" << endl;
    // State = 1 for cluster
    // State = -1 for occupied

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            if (grid[i][j] ==  1) {
                output << i << ", " << j << ", 0, 1" << endl;
            }
        }
    }

    for (auto & i : particleList) {
        output << i.x << ", " << i.y << ", 0, -1" << endl;
    }

    output.close();
}

int main() {

    // Create walker
    walker *particle;

    cout << "Simulating " << numberOfWalkers << " particles taking " << numberOfWalkerSteps << " steps" << endl;

    // Create clusterGrid to store particles in
    int clusterGrid[width][height];

    // Fill clusterGrid with zeros
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j <= height; j++) {
            clusterGrid[i][j] = 0;
        }
    }

    // One particle at the centre
    clusterGrid[width / 2][height / 2] = 1;
//    clusterGrid[20][20] = 1;
//    clusterGrid[480][480] = 1;


    // Output
    int time = 0;
    writeToCSV(time, clusterGrid);
    int n = 1;

    for (time = 1; time < numberOfWalkerSteps; time++) {
//        cout << time << endl;

        if (time % 1000 == 0){
            cout << time << endl;
        }

        for (auto & i : particleList) {
//            cout << time << " " << particle.x << ", " << particle.y << endl;
            particle = &i;
            if (particle -> active) {
                particle->takeRandomStep();
                if  (particle->touchingCluster(clusterGrid)){
                    clusterGrid[particle->x][particle->y] = 1;
                    n++;
//                    writeToCSV(n, clusterGrid); // Animate by growth
                    particle -> reset();
                    if (particle->touchingCluster(clusterGrid)) particle -> active = false;
                }
            }
        }
        writeToCSV(time, clusterGrid); // Animation by time for all particles
    }

//    writeToCSV(time, clusterGrid); // Animation by time for all particles

    cout << "Cluster Size: " << n << endl;


    return 0;
}