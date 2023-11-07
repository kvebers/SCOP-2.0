#ifndef MODELS_HPP
#define MODELS_HPP

#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
// #include "/Users/kvebers/.brew/Cellar/glfw/3.3.8/include/GLFW/glfw3.h"
#include "helper.hpp"
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <algorithm>
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
  GLFWwindow *_window;
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
  ~Models();
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
void setupGLFW(WindowManager &window);

#endif