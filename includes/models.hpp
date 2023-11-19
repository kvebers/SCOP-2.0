#ifndef MODELS_HPP
#define MODELS_HPP

#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
// #include "/Users/kvebers/.brew/Cellar/glfw/3.3.8/include/GLFW/glfw3.h"
#include "Material.hpp"
#include "WindowManager.hpp"
#include "helper.hpp"
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Models {
public:
  vector<Vec3 *> _points;
  vector<Vec3 *> _vt;
  vector<Triangles> _triangles;
  string _objectName;
  GLuint _texture;
  int _currentTexture;
  int _initState;
  bool _uvMap;

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
  void Shader(Vec3 *point, WindowManager &window, vector<Material> &material);
  void normalize();
  void updateShape(WindowManager &window);
  void drawTriangles(WindowManager &window, vector<Material> &materials);
  void drawTriangle(WindowManager &window, Triangles &triangle,
                    vector<Material> &materials);
  void rotateShape(WindowManager &window);
  void centerObject();
  void moveShape(WindowManager &window);
  void calculateMedium();
  void processTexture(std::string &point1, std::string &point2,
                      std::string &point3, Triangles &tri, vector<Vec3 *> &vec);
  void loadTexture();
  void generateUvMap();
  void createTexturePoints();
  void normTexture();
  void drawPoints(WindowManager &window, Triangles &triangle,
                  vector<Material> &materials);
  void drawLines(WindowManager &window, Triangles &triangle,
                 vector<Material> &materials);
};

void draw(vector<Models> &models, WindowManager &window,
          vector<Material> &material);
void setupGLFW(WindowManager &window, std::vector<Models> &models);
string replaceModelWithPath(string modelPath);

#endif