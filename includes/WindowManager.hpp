#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include "Material.hpp"
#include "helper.hpp"
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

class WindowManager {
public:
  int _currentWindow;
  GLFWwindow *_window;
  float _proportion;
  bool _isRotating;
  bool _isMoving;
  Material *_material;
  float _lastCursorX;
  float _lastCursorY;
  float _moveX;
  float _moveY;
  float _rotateX;
  float _rotateY;
  int _mode;
  float _zoom;
  bool _ceneterObject;
  Vec3 _lightData;
  Vec3 _lightColor;
  Vec3 _viewPos;
  int _sign;
  float _moveZ;
  void setupData();
  static void cursorPositionCallback(GLFWwindow *window, double xpos,
                                     double ypos);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);
  static void windowSizeCallback(GLFWwindow *window, int width, int height);
  static void scrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);
};

#endif