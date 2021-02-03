#include <iostream>
#include <stdio.h>
// following line is needed so that M_PI gives value of pi
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Planet {
  public:
    // default constructor
    Planet() { ; } // do nothing 
    
    // another constructor ( defined below main() )
    Planet(double _mass, double _radius);  

    // member variables (properties of the Planet)
    double mass;
    double radius;

    // member functions ( defined below main() )
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

  // declare a new planet and set its mass and radius
  Planet jupiter(1.9e27,7e7);

  cout << "jupiter density is " << jupiter.Density() << " (SI units, accuracy 1 sig fig)" << endl;

  cout << "Hit enter to exit" << endl;
  cin.get();
  return 0;
}

Planet::Planet(double _mass, double _radius) {
  mass = _mass; radius = _radius;
}

double Planet::Volume() { 
      return 4.0 * M_PI * radius * radius * radius / 3.0;
} 

double Planet::Density() {
      return mass / Volume();
}
