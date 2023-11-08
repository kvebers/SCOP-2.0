#include "../includes/models.hpp"

void WindowManager::cursorPositionCallback(GLFWwindow *window, double xpos,
                                           double ypos) {
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));

  if (windowManager._isRotating) {
    double deltaX = xpos - windowManager._lastCursorX;
    double deltaY = ypos - windowManager._lastCursorY;
    const float sensitivity = 0.5f;
    windowManager._rotateX += static_cast<float>(deltaY) * sensitivity;
    windowManager._rotateY += static_cast<float>(deltaX) * sensitivity;
    windowManager._lastCursorX = xpos;
    windowManager._lastCursorY = ypos;
  }
}

void WindowManager::keyCallback(GLFWwindow *window, int key, int scancode,
                                int action, int mods) {
  (void)scancode;
  (void)mods;
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    windowManager._currentWindow++;
}

void WindowManager::mouseButtonCallback(GLFWwindow *window, int button,
                                        int action, int mods) {
  (void)mods;
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {

      windowManager._isRotating = true;
    } else if (action == GLFW_RELEASE) {
      windowManager._isRotating = false;
    }
  }
}

void WindowManager::windowSizeCallback(GLFWwindow *window, int width,
                                       int height) {
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
  windowManager._proportion =
      static_cast<float>(width) / static_cast<float>(height);
  glViewport(0, 0, width, height);
  (void)windowManager;
}
