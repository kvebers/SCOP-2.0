#include "../includes/models.hpp"
#include <vector>

void setupGLFW(WindowManager &window, std::vector<Models> &models) {
  window._window = glfwCreateWindow(2560, 1920, "SCOP", NULL, NULL);
  if (!window._window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(127);
  }
  glfwMakeContextCurrent(window._window);
  for (auto &it : models)
    it.loadTexture();
  window._currentWindow = 0;
}

void WindowManager::setupData() {
  int width, height;
  glfwGetWindowSize(_window, &width, &height);
  _proportion =
      (width > 0 && height > 0) ? (static_cast<float>(width) / height) : 1.0f;
  glfwSetWindowUserPointer(_window, this);
  glfwSetKeyCallback(_window, WindowManager::keyCallback);
  glfwSetMouseButtonCallback(_window, WindowManager::mouseButtonCallback);
  glfwSetCursorPosCallback(_window, WindowManager::cursorPositionCallback);
  glfwSetWindowSizeCallback(_window, WindowManager::windowSizeCallback);
  _lightData.x = 5.0f;
  _lightData.y = -2.0f;
  _lightData.z = 3.0f;
  _lightColor.x = 1.0f;
  _lightColor.y = 1.0f;
  _lightColor.z = 1.0f;
  _viewPos.x = 0.0f;
  _viewPos.y = 0.0f;
  _viewPos.z = 0.0f;
  _isMoving = false;
  _isRotating = false;
}