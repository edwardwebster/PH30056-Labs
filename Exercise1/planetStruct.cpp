#include <iostream>
#include <stdio.h>
// following line is needed so that M_PI gives value of pi
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

typedef struct pt {
  float mass;
  float radius;
} Planet;

int main( int argc, char *argv[] ) {
  // declare a new planet
  Planet earth;

  earth.mass = 6e24;
  earth.radius = 6.4e6;

  double volume = 4.0 * M_PI * earth.radius * earth.radius * earth.radius / 3.0;
  double density = earth.mass / volume;

  cout << "earth density is " << density << " (SI units)" << endl;

  cout << "Hit enter to exit" << endl;
  cin.get();
  return 0;
}
