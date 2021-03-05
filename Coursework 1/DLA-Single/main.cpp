//
// Created by Edward Webster on 20/01/2021.
//
#include <iostream>
#include <fstream>
#include "cxxopts.hpp"
#include "randomGenerator.h"

using namespace std;

//int width = 550;
//int height = 550;
int numberOfWalkers = 3000;
int numberOfWalkerSteps=  20000;
float stickingProbability = 0.5;
string outputFolder = "../Data/DLA-Single/";
string outputFilename = "output.csv.";
bool verbose = true;

#define width 500
#define height 500
//#define numberOfWalkers 3000
//#define numberOfWalkerSteps 20000
//#define stickingProbability 1.00
//#define outputFile "../Data/DLA-Single/output.csv."

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

                    if (randomBetween(0, 10000) / 10000 < stickingProbability) {
                        active = false;
                        return true;
                    } else {
                    }

                }

            }
        }

        return false;
    }

    void takeRandomStep() {
        // Update position by moving up, down, left or right
        if (not active) return;

        x += int(randomBetween(-1, 1));
        y += int(randomBetween(-1, 1));
        //z += randomBetween(-1, 1);

        // Cannot leave boundary
        if (x == 0) x++;
        if (x == width) x--;

        if (y == 0) y++;
        if (y == height) y--;

    }

    walker() {
        x = int(randomBetween(1, width - 1));
        y = int(randomBetween(1, height - 1));
        active = true;
    };
};

void writeToCSV(int time, int grid[width][height]) {
    ofstream output;
    output.open(outputFolder + outputFilename + to_string(time));

    output << "x,y,z,state,r" << endl;
    // State = 1 for cluster
    // State = -1 for occupied

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            if (grid[i][j] == 1) {
                output << i << ", " << j << ", 0, 1, "
                       << sqrt((i - width / 2.) * (i - width / 2.) + (j - height / 2.) * (j - height / 2.)) + 1 << endl;
            }
        }
    }

//    for (auto &i : particleList) {
//        output << i.x << ", " << i.y << ", 0, -1" << endl;
//    }

    output.close();
}

int main(int argc, char** argv) {

    cxxopts::Options options("DLA Single", "Single particle simulation of Diffusion Limited Aggregation");
    options.add_options()
            ("h,help", "prints this message")
            ("w,width", "width of the simulation grid (inactive)", cxxopts::value<int>()->default_value("500"))
            ("l,length", "height of the simulation grid (inactive)", cxxopts::value<int>()->default_value("500"))
            ("n,number", "number of simulated walkers", cxxopts::value<int>()->default_value("5000"))
            ("s,steps", "number of walker steps", cxxopts::value<int>()->default_value("20000"))
            ("p,probability", "sticking probability", cxxopts::value<float>()->default_value("1.0"))
            ("o,outputfolder", "output folder", cxxopts::value<string>()->default_value("../../Data/DLA-Single/"))
            ("f,outputfile", "output file names <filename>.csv.<timestep>", cxxopts::value<string>()->default_value("output.csv."))
            ("v,verbose", "verbose output", cxxopts::value<bool>()->default_value("false"))
            ;

    auto result = options.parse(argc, argv);

    if (result.count("help")){

        cout << options.help() << endl;

        return 0;
    }

//    width = result["width"].as<int>();
//    height = result["length"].as<int>();
    numberOfWalkers = result["number"].as<int>();
    numberOfWalkerSteps = result["steps"].as<int>();
    stickingProbability = result["probability"].as<float>();
    outputFolder = result["outputfolder"].as<string>();
    outputFilename = result["outputfile"].as<string>();
    verbose = result["verbose"].as<bool>();

    if (not verbose) {
        cout << "Verbose Output" << endl;
        cout << "Simulating " << numberOfWalkers << " particles taking " << numberOfWalkerSteps << " steps" << endl;
        cout << "Sticking probability = " << stickingProbability << endl;
        cout << "Data generated in " << outputFolder << outputFilename << "*" << endl;
    } else if (verbose) {
        printf("x,y,z,state,n");
    }
    // Create walker
    walker *particle;

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

    // Output
    int time = 0;
    writeToCSV(time, clusterGrid);

    int n = 1;
    while (n <= numberOfWalkers) {
        particle = new walker;
        for (time = 1; time < numberOfWalkerSteps; time++) {
            particle->takeRandomStep();
            if (particle->touchingCluster(clusterGrid)) {
                n++;
                clusterGrid[particle->x][particle->y] = 1;

                if (not verbose) {
                    writeToCSV(n, clusterGrid);
                } else if (verbose) {
                    int x = particle->x;
                    int y = particle->y;
                    printf("%d,%d,0,1,%f,%d\n", x, y, sqrt((x - width / 2.) * (x - width / 2.) + (y - height / 2.) * (y - height / 2.)), n);
                }

                break;
            }
            //writeToCSV(time, clusterGrid); // Can either animate by particle step

        }
        delete particle;
//        writeToCSV(n, clusterGrid); // Or animate by particle
//        n++;
    }
    return 0;
}