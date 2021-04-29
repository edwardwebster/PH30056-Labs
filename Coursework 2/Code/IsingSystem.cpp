//
//  IsingSystem.cpp
//

#include "IsingSystem.h"

// colors
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
namespace colours {
    // note the f's here avoid warnings by telling C++ to read the numbers as floats and not doubles
    GLfloat blue[] = {0.1f, 0.3f, 0.9f, 1.0f};   // blue
    GLfloat red[] = {1.0f, 0.2f, 0.1f, 0.2f};   // red
    GLfloat green[] = {0.3f, 0.6f, 0.3f, 1.0f};   // green
}


// constructor
IsingSystem::IsingSystem(Window *set_win) {
    cout << "creating system, gridSize " << gridSize << endl;
    win = set_win;

    inverseTemperatureBeta = 1 / 4.0;
    slowNotFast = 1;
    isActive = 0;
    numberOfSteps = 0;

    // Open the logfile
//    string filename = "../Data/" + to_string(inverseTemperatureBeta) + ".csv";
//    logfile.open(filename);
//    logfile.open("../Data/output.csv");
//    logfile << "Grid Size: " << gridSize << ',' << gridSize << endl;
//    logfile << "Inverse temperature: " << inverseTemperatureBeta << endl;
//    logfile << "time,energy,magnetisation\n";

    // Allocate memory for the grid, remember to free the memory in destructor
    //   the point here is that each row of the grid is an array
    //   the grid itself is a an array of pointers, one for each row
    // Here we allocate the array of pointers
    grid = new int *[gridSize];
    // Now allocate the individual rows
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new int[gridSize];
    }

    // this sets the temperature and initialises the spins grid
    Reset();
}

void IsingSystem::Reset() {

    double initialTemp = 4.0;

    setTemperature(initialTemp);

    // set the grid to -1
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            // position is (i,j)
            int pos[2] = {i, j};
            // set this spin to state -1
            setGrid(pos, -1);
        }
    }

    numberOfSteps = 0;

}


// destructor
IsingSystem::~IsingSystem() {
    // Close the file (if open)
    if (logfile.is_open())
        logfile.close();

    // Delete the window
    delete win;

    // Delete the grid
    // First we delete the individual rows
    for (int i = 0; i < gridSize; i++)
        delete[] grid[i];
    // Finally delete the array of pointers
    delete[] grid;
}

// this draws the system
void IsingSystem::DrawSquares() {

    double drawScale = 2.0 / (gridSize * 1.1);

    // draw the particles
    double halfSize = 0.5;
    int halfGrid = gridSize / 2;
    for (int x = 0; x < gridSize; x++) {
        for (int y = 0; y < gridSize; y++) {

            double vec[2];
            vec[0] = x - halfGrid;
            vec[1] = y - halfGrid;

            // openGL magic
            glPushMatrix();
            // choose a color
            if (grid[x][y] == -1)
                glColor4fv(colours::green);
            else
                glColor4fv(colours::blue);
            // draw a rectangle for the particle
            glRectd(drawScale * (vec[0] - halfSize),
                    drawScale * (vec[1] - halfSize),
                    drawScale * (vec[0] + halfSize),
                    drawScale * (vec[1] + halfSize));
            // openGL magic
            glPopMatrix();
        }
    }

    // print some information (at top left)
    // this ostringstream is a way to make a string with numbers and words (similar to cout << ... )
    ostringstream str;
    str << "beta " << inverseTemperatureBeta << " size " << gridSize;
    win->displayString(str, -0.9, 0.94, colours::red);

}


// attempt N spin flips, where N is the number of spins
void IsingSystem::MCsweep() {
    for (int i = 0; i < gridSize * gridSize; i++)
        attemptSpinFlip();
}

// here we attempt to flip a spin and accept/reject with Metropolis rule
void IsingSystem::attemptSpinFlip() {
    int pos[2];

    // random site
    pos[0] = rgen.randomInt(gridSize);
    pos[1] = rgen.randomInt(gridSize);

    double hloc = computeLocalField(pos);

    double dE = 2.0 * hloc * readGrid(pos);
    if (dE < 0)
        flipSpin(pos);

    // TODO - This wasn't multiplied by inverseTemperatureBeta
    //        Ask why it wasn't in class
//    else if (rgen.random01() < exp(-dE * inverseTemperatureBeta))
    else if (rgen.random01() < exp(-dE))
        flipSpin(pos);

}

// NOTE: this returns the local field *divided by the temperature* (dimensionless quantity)
double IsingSystem::computeLocalField(int pos[]) {
    double result = 0.0;
    for (int i = 0; i < 4; i++) {
        int nborPos[2];
        setPosNeighbour(nborPos, pos, i);
        result += readGrid(nborPos);
    }
    result *= inverseTemperatureBeta;
    return result;
}

// set the value of a grid cell for a particular position
void IsingSystem::setGrid(int pos[], int val) {
    grid[pos[0]][pos[1]] = val;
}

// read the grid cell for a given position
int IsingSystem::readGrid(int pos[]) {
    return grid[pos[0]][pos[1]];
}

// flip the grid cell for a given position
void IsingSystem::flipSpin(int pos[]) {
    grid[pos[0]][pos[1]] = -grid[pos[0]][pos[1]];
}


// send back the position of a neighbour of a given grid cell
// NOTE: we take care of periodic boundary conditions, also positions are integers now not doubles
void IsingSystem::setPosNeighbour(int setpos[], int pos[], int val) {
    switch (val) {
        case 0:
            setpos[0] = (pos[0] + 1) % gridSize;
            setpos[1] = pos[1];
            break;
        case 1:
            setpos[0] = (pos[0] - 1 + gridSize) % gridSize;
            setpos[1] = pos[1];
            break;
        case 2:
            setpos[0] = pos[0];
            setpos[1] = (pos[1] + 1) % gridSize;
            break;
        case 3:
            setpos[0] = pos[0];
            setpos[1] = (pos[1] - 1 + gridSize) % gridSize;
            break;
    }
}

// this is the update function which at the moment just does one mc sweep
void IsingSystem::Update() {
    numberOfSteps += 1;

    if (numberOfSteps % 1 == 0 && numberOfSteps > 0) {
        logfile << numberOfSteps << ',' << inverseTemperatureBeta << ',' << getSystemEnergy() << ',' << getSystemMagnetisation()
            << ',' << correlation(25, 25, 26, 26)
            << ','<< correlation(25, 25, 37, 37)
            << ',' << correlation(25, 25, 49, 49) << endl;
//        logfile << numberOfSteps << ',' << inverseTemperatureBeta << ',' << getSystemEnergy() << ',' << getSystemMagnetisation() << endl;
    }

    if (numberOfSteps % 1000 == 0) {
        cout << "Steps taken:\t" << numberOfSteps << endl;
    }

    if (numberOfSteps % 1000 == 0) {
        inverseTemperatureBeta -= 0.025;
//        cout << "Temperature: " << inverseTemperatureBeta << endl;
    }

    MCsweep();
}

double IsingSystem::getSystemEnergy() {

    // Energy in units of kB*T

    double systemEnergy = 0.;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            // position is (i,j)
            int pos[2] = {i, j};
            // set this spin to state -1
            systemEnergy += computeLocalField(pos)*readGrid(pos);
        }
    }

    systemEnergy /= 2*gridSize*gridSize;

    return systemEnergy;
}

double IsingSystem::getSystemMagnetisation() {

    double magnetisation = 0.;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {

            int pos[2] = {i, j};

            magnetisation += (double) readGrid(pos);
        }
    }
//    cout << magnetisation << endl;

    magnetisation /= gridSize*gridSize;
//    magnetisation /= gridSize;

    return magnetisation;
}

double IsingSystem::getHeatCapacity() {

    double averageSquaredEnergy = 0.;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            // position is (i,j)
            int pos[2] = {i, j};
            // set this spin to state -1
            averageSquaredEnergy += computeLocalField(pos)*computeLocalField(pos);
        }
    }

    averageSquaredEnergy /= gridSize*gridSize;

    averageSquaredEnergy -= getSystemEnergy()*getSystemEnergy();

    return averageSquaredEnergy;
}

double IsingSystem::getMagneticSusceptibility() {

    double averageSquaredMagnetism = 0.;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            // position is (i,j)
            int pos[2] = {i, j};
            // set this spin to state -1
            averageSquaredMagnetism += readGrid(pos)*readGrid(pos);
        }
    }

    averageSquaredMagnetism /= gridSize*gridSize;

    averageSquaredMagnetism -= getSystemMagnetisation()*getSystemMagnetisation();

    return averageSquaredMagnetism;

}

void IsingSystem::setRunning() {
    isActive = 1;
    string filename = "/Users/Edward/OneDrive - University of Bath/Physics/Year 3/Semester 2/Comp B/Labs/Coursework 2/Data/" + to_string(inverseTemperatureBeta) + ".csv";
    logfile.open(filename);
//        logfile.open("../Data/output.csv");
    logfile << "Grid Size: " << gridSize << ',' << gridSize << endl;
    logfile << "Inverse temperature: " << inverseTemperatureBeta << endl;
    logfile << "time,beta,energy,magnetisation,cor1,cor2,cor3\n";
}

void IsingSystem::pauseRunning() {
    isActive = 0;
    logfile.close();
}

int IsingSystem::correlation(int x1, int y1, int x2, int y2) {

    int pos1[2] = {x1, y1};
    int pos2[2] = {x2, y2};

    return readGrid(pos1)*readGrid(pos2);
}

#pragma clang diagnostic pop