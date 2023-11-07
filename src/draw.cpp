#include "../includes/models.hpp"
#include <vector>



void drawTriangle(draw) {

}

void renderLoop(WindowManager &window, vector<Models> &models) {
  (void)models;
  while (!glfwWindowShouldClose(window._window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawTriangle();
    glfwSwapBuffers(window._window);
    glfwPollEvents();
  }
}

void draw(vector<Models> &models, WindowManager &window) {
  setupGLFW(window);
  renderLoop(window, models);
}