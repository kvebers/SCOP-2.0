#include "../includes/models.hpp"

void WindowManager::cursorPositionCallback(GLFWwindow *window, double xpos,
                                           double ypos) {
  auto &windowManager =
      *static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
  if (windowManager._isRotating || windowManager._isMoving) {
    double deltaX = xpos - windowManager._lastCursorX;
    double deltaY = ypos - windowManager._lastCursorY;
    float sens = 0.5f;
    windowManager._rotateX += static_cast<float>(deltaY) * sens;
    windowManager._rotateY += static_cast<float>(deltaX) * sens;
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
  if (key == GLFW_KEY_S && action == GLFW_PRESS)
    windowManager._mode++;
  if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
    windowManager._sign = 1;
  if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
    windowManager._sign = -1;
  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
    windowManager._material->Ka.x += windowManager._sign * 0.05;
    if (windowManager._material->Ka.x < 0)
      windowManager._material->Ka.x = 0;
    if (windowManager._material->Ka.x > 1)
      windowManager._material->Ka.x = 1;
  }
  if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
    windowManager._material->Ka.y += windowManager._sign * 0.05;
    if (windowManager._material->Ka.y < 0)
      windowManager._material->Ka.y = 0;
    if (windowManager._material->Ka.y > 1)
      windowManager._material->Ka.y = 1;
  }
  if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
    windowManager._material->Ka.z += windowManager._sign * 0.05;
    if (windowManager._material->Ka.z < 0)
      windowManager._material->Ka.z = 0;
    if (windowManager._material->Ka.z > 1)
      windowManager._material->Ka.z = 1;
  }
  if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
    windowManager._material->Kd.x += windowManager._sign * 0.05;
    if (windowManager._material->Kd.x < 0)
      windowManager._material->Kd.x = 0;
    if (windowManager._material->Kd.x > 1)
      windowManager._material->Kd.x = 1;
  }
  if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
    windowManager._material->Kd.y += windowManager._sign * 0.05;
    if (windowManager._material->Kd.y < 0)
      windowManager._material->Kd.y = 0;
    if (windowManager._material->Kd.y > 1)
      windowManager._material->Kd.y = 1;
  }
  if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
    windowManager._material->Kd.z += windowManager._sign * 0.05;
    if (windowManager._material->Kd.z < 0)
      windowManager._material->Kd.z = 0;
    if (windowManager._material->Kd.z > 1)
      windowManager._material->Kd.z = 1;
  }
  if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
    windowManager._material->Ks.x += windowManager._sign * 0.05;
    if (windowManager._material->Ks.x < 0)
      windowManager._material->Ks.x = 0;
    if (windowManager._material->Ks.x > 1)
      windowManager._material->Ks.x = 1;
  }
  if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
    windowManager._material->Ks.y += windowManager._sign * 0.05;
    if (windowManager._material->Ks.y < 0)
      windowManager._material->Ks.y = 0;
    if (windowManager._material->Ks.y > 1)
      windowManager._material->Ks.y = 1;
  }
  if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
    windowManager._material->Ks.z += windowManager._sign * 0.05;
    if (windowManager._material->Ks.z < 0)
      windowManager._material->Ks.z = 0;
    if (windowManager._material->Ks.z > 1)
      windowManager._material->Ks.z = 1;
  }
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