#ifndef MODELS_HPP
#define MODELS_HPP

#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
// #include "/Users/kvebers/.brew/Cellar/glfw/3.3.8/include/GLFW/glfw3.h"
#include "Material.hpp"
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
  int _currentWindow;
  GLFWwindow *_window;
  float _proportion;
  bool _isRotating;
  float _lastCursorX;
  float _lastCursorY;
  float _moveX;
  float _moveY;
  float _rotateX;
  float _rotateY;
  bool _ceneterObject;
  Vec3 _lightData;
  Vec3 _lightColor;
  Vec3 _viewPos;
  float _rotateZ;
  void setupData();
  static void cursorPositionCallback(GLFWwindow *window, double xpos,
                                     double ypos);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);
  static void windowSizeCallback(GLFWwindow *window, int width, int height);
};

class Models {
public:
  vector<Vec3 *> _points;
  vector<Vec3 *> _vt;
  vector<Triangles> _triangles;
  string _objectName;
  string _texture;
  int _currentTexture;
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
  void Shader(Vec3 *point, WindowManager &window, vector<Material> &material);
  void normalize();
  void updateShape(WindowManager &window);
  void drawTriangles(WindowManager &window, vector<Material> &materials);
  void drawTriangle(WindowManager &window, Triangles &triangle,
                    vector<Material> &materials);
  void centerObject();
};

void draw(vector<Models> &models, WindowManager &window,
          vector<Material> &material);
void setupGLFW(WindowManager &window);

#endif