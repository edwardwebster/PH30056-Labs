//
// Created by Edward Webster on 20/01/2021.
//
#include <iostream>
#include <fstream>
#include "randomGenerator.h"

using namespace std;

#define width 50
#define height 50
#define depth 50
#define numberOfWalkers 1000
#define numberOfWalkerSteps 1000
#define stickingProbability 0.9
#define outputFile "output/output.csv."

class walker {
public:
    int x, y, z;
    bool active;

    bool touchingCluster(int cluster[width][height][depth]) {

        if (not active) return true;

        // For loop over x, y, z
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {

                    if (x + i == 0 || x + i == width) return false;
                    if (y + j == 0 || y + j == height) return false;
                    if (z + k == 0 || z + k == height) return false;

                    if (cluster[x + i][y + j][z + k] == 1) {
                        active = false;
                        return true;
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
        z += randomBetween(-1, 1);
        //z += randomBetween(-1, 1);

        // Cannot leave boundary
        if (x == 0) x++;
        if (x == width) x--;

        if (y == 0) y++;
        if (y == height) y--;

        if (z == 0) z++;
        if (z == height) z--;

    }

    walker() {
        x = randomBetween(0, width - 1);
        y = randomBetween(0, height - 1);
        z = randomBetween(0, depth - 1);
        active = true;
    };
};

walker particleList[numberOfWalkers];

void writeToCSV(int time, int grid[width][height][depth]) {
    ofstream output;
    output.open(outputFile + to_string(time));

    output << "x, y, z, state" << endl;
    // State = 1 for cluster
    // State = -1 for occupied

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < depth; k++) {
                if (grid[i][j][k] == 1) {
                    output << i << ", " << j << "," << k << ", 1" << endl;
                }
            }
        }
    }

    for (auto &i : particleList) {
        output << i.x << ", " << i.y << ", " << i.z << ", -1" << endl;
    }

    output.close();
}

int main() {

    // Create walker
    walker *particle;

    cout << "Simulating " << numberOfWalkers << " particles taking " << numberOfWalkerSteps << " steps" << endl;

    // Create clusterGrid to store particles in
    int clusterGrid[width][height][depth];

    // Fill clusterGrid with zeros
    for (int i = 0; i < width; i++) {
        for (int j = 0; j <= height; j++) {
            for (int k = 0; k <= depth; k++) {
                clusterGrid[i][j][k] = 0;
            }
        }
    }

    // One particle at the centre
    clusterGrid[width / 2][height / 2][depth/2] = 1;

    // Output
    int time = 0;
    writeToCSV(time, clusterGrid);


    for (time = 1; time < numberOfWalkerSteps; time++) {
        for (auto &i : particleList) {
            particle = &i;
            particle->takeRandomStep();
            if (particle->touchingCluster(clusterGrid)) {
                clusterGrid[particle->x][particle->y][particle->z] = 1;
            }
        }
        writeToCSV(time, clusterGrid);
    }
    return 0;
}