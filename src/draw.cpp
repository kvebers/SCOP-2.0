#include "../includes/models.hpp"
#include <vector>

void Models::drawTriangle(WindowManager &window, Triangles &triangle,
                          vector<Material> &materials) {
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 3; i++) {
    Shader(triangle.points[i], window, materials);
    glTexCoord2f(triangle.textures[i]->x, triangle.textures[i]->y);
    glVertex3f(triangle.points[i]->x / window._proportion,
               triangle.points[i]->y, triangle.points[i]->z);
  }
  glEnd();
}

void Models::drawTriangles(WindowManager &window, vector<Material> &materials) {
  for (Triangles &it : _triangles)
    drawTriangle(window, it, materials);
}

void renderLoop(WindowManager &window, vector<Models> &models,
                vector<Material> &materials) {
  while (!glfwWindowShouldClose(window._window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (materials[models[window._currentWindow % models.size()]._currentTexture]
            .d < 1) {
      glDepthMask(GL_FALSE);
      glEnable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
    } else {
      glDepthMask(GL_TRUE);
      glDisable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,
                  models[window._currentWindow % models.size()]._texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    models[window._currentWindow % models.size()].updateShape(window);
    models[window._currentWindow % models.size()].drawTriangles(window,
                                                                materials);
    glfwSwapBuffers(window._window);
    glfwPollEvents();
  }
}

void draw(vector<Models> &models, WindowManager &window,
          vector<Material> &materials) {
  setupGLFW(window, models);
  window.setupData();
  glDepthRange(0, 3);
  renderLoop(window, models, materials);
}