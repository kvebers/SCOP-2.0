#ifndef MODELS_HPP
#define MODELS_HPP

#include "helper.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class WindowManager {
public:
  int currentWindow;
};

class Models {
public:
  vector<Vec3 *> _points;
  vector<Vec3 *> _vt;
  vector<Triangles> _triangles;
  string _objectName;
  string _texture;
  int _initState;
  Models(string objectName);
  void addPoint(string line, vector<Vec3 *> &vec);
  void readPoints();
  void readTriangles();
  void splitQuadsInTriangles();
  void processPoint(std::string &point1, std::string &point2,
                    std::string &point3, Triangles &tri, vector<Vec3 *> &vec);
  void createTriangle(std::string &point1, std::string &point2,
                      std::string &point3);
};

void draw(vector<Models> &models, WindowManager &window);

#endif