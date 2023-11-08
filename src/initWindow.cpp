#include "../includes/models.hpp"
#include <vector>

void setupGLFW(WindowManager &window) {
  window._window = glfwCreateWindow(2560, 1920, "SCOP", NULL, NULL);
  if (!window._window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(127);
  }
  glfwMakeContextCurrent(window._window);
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
}