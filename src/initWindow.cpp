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
  window.currentWindow = 0;
}