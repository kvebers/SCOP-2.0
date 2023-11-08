#include "../includes/models.hpp"
#include <vector>

void drawTriangle(WindowManager &window, Triangles &triangle) {
  (void)window;
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 3; i++) {
    glVertex3f(triangle.points[i]->x / window._proportion,
               triangle.points[i]->y, triangle.points[i]->z);
  }
  glEnd();
}

void drawTriangles(WindowManager &window, Models &model) {
  for (Triangles &it : model._triangles)
    drawTriangle(window, it);
}

void updateShape(WindowManager &window, Models &model) {
  float rotateXRad = window._rotateX * M_PI / 180.0f;
  float rotateYRad = window._rotateY * M_PI / 180.0f;
  float cosX = cos(rotateXRad);
  float sinX = sin(rotateXRad);
  float cosY = cos(rotateYRad);
  float sinY = sin(rotateYRad);
  for (Vec3 *point : model._points) {
    float yNew = point->y * cosX - point->z * sinX;
    float zNew = point->y * sinX + point->z * cosX;
    point->y = yNew;
    point->z = zNew;
    float xNew = point->x * cosY + point->z * sinY;
    zNew = -point->x * sinY + point->z * cosY;
    point->x = xNew;
    point->z = zNew;
  }
  window._rotateX = 0;
  window._rotateY = 0;
}

void renderLoop(WindowManager &window, vector<Models> &models) {
  while (!glfwWindowShouldClose(window._window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    updateShape(window, models[window._currentWindow % models.size()]);
    drawTriangles(window, models[window._currentWindow % models.size()]);
    glfwSwapBuffers(window._window);
    glfwPollEvents();
  }
}

void draw(vector<Models> &models, WindowManager &window) {
  setupGLFW(window);
  window.setupData();
  renderLoop(window, models);
}