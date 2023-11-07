#include "../includes/models.hpp"
#include <vector>

void drawTriangle(WindowManager &window, Triangles &triangle) {
  (void)window;
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 3; i++) {
    glVertex3f(triangle.points[i]->x, triangle.points[i]->y,
               triangle.points[i]->z);
  }
  glEnd();
}

void drawTriangles(WindowManager &window, Models &model) {
  for (Triangles &it : model._triangles)
    drawTriangle(window, it);
}

void renderLoop(WindowManager &window, vector<Models> &models) {
  (void)models;
  while (!glfwWindowShouldClose(window._window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawTriangles(window, models[window.currentWindow]);
    glfwSwapBuffers(window._window);
    glfwPollEvents();
  }
}

void draw(vector<Models> &models, WindowManager &window) {
  setupGLFW(window);
  renderLoop(window, models);
}