#include <iostream>
#include <stdio.h>
// following line is needed so that M_PI gives value of pi
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Planet {
  public:
    // member variables
    double mass;
    double radius;

    // member functions (defined below)
    double Volume();
    double Density();
};

int main( int argc, char *argv[] ) {
  // declare a new planet
  Planet earth;

  earth.mass = 6e24;
  earth.radius = 6.4e6;

  double density = earth.Density();

  cout << "earth density is " << density << " (SI units, accuracy 1 sig fig)" << endl;

  Planet jupiter;

  jupiter.mass = 1.9e27;
  jupiter.radius = 7e7;
  
  cout << "jupiter density is " << jupiter.Density() << " (SI units, accuracy 1 sig fig)" << endl;

  cout << "Hit enter to exit" << endl;
  cin.get();
  return 0;
}

double Planet::Volume() { 
      return 4.0 * M_PI * radius * radius * radius / 3.0;
} 

double Planet::Density() {
      return mass / Volume();
}
