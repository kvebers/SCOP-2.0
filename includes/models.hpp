#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Vec3 {
public:
  double x, y, z;
  Vec3(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
};

class Texture {
public:
  Vec3 points[3];
};

class Triangles {
public:
  Vec3 points[3];
  vector<Texture> textures;
};

class Models {
public:
  vector<float> points;
  vector<Triangles> _triangles;
  string _objectName;
  string _texture;
  int _initState;
  Models(string objectName);
};

#endif