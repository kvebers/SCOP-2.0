#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Vec3 {
public:
  float x, y, z;
  Vec3(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
  Vec3() : x(0), y(0), z(0) {}
};

class Triangles {
public:
  Vec3 *points[3];
  Vec3 *textures[3];
  int connections[3];
  float avg;
  Triangles() {
    for (int i = 0; i < 3; ++i)
      points[i] = nullptr;
  }
};

#endif