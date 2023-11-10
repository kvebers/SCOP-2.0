#include "../includes/models.hpp"

void WindowManager::cursorPositionCallback(GLFWwindow *window, double xpos,
                                           double ypos) {
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));

  if (windowManager._isRotating || windowManager._isMoving) {
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
  if (key == GLFW_KEY_A && action == GLFW_PRESS)
    windowManager._ceneterObject = true;
}

void WindowManager::mouseButtonCallback(GLFWwindow *window, int button,
                                        int action, int mods) {
  (void)mods;
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS)
      windowManager._isRotating = true;
    else if (action == GLFW_RELEASE)
      windowManager._isRotating = false;
  }
  if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    if (action == GLFW_PRESS)
      windowManager._isMoving = true;
    else if (action == GLFW_RELEASE)
      windowManager._isMoving = false;
  }
}

void WindowManager::windowSizeCallback(GLFWwindow *window, int width,
                                       int height) {
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
  glfwGetWindowSize(window, &width, &height);
  windowManager._proportion =
      (width > 0 && height > 0) ? (static_cast<float>(width) / height) : 1.0f;
  glViewport(0, 0, width, height);
  (void)windowManager;
}

void WindowManager::scrollCallback(GLFWwindow *window, double xoffset,
                                   double yoffset) {
  (void)xoffset;
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
  windowManager._zoom += static_cast<float>(yoffset / 10);
}