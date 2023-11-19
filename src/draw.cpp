#include "../includes/models.hpp"
#include <OpenGL/OpenGL.h>
#include <vector>

void Models::drawTriangle(WindowManager &window, Triangles &triangle,
                          vector<Material> &materials) {
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 3; i++) {
    Shader(triangle.points[i], window, materials);
    glTexCoord2f(triangle.textures[i]->x, triangle.textures[i]->y);
    glVertex3f(triangle.points[i]->x / window._proportion / window._zoom,
               triangle.points[i]->y / window._zoom,
               triangle.points[i]->z / window._zoom);
  }
  glEnd();
}

void Models::drawPoints(WindowManager &window, Triangles &triangle,
                        vector<Material> &materials) {
  glPointSize(6);
  glBegin(GL_POINTS);
  for (int i = 0; i < 3; i++) {
    Shader(triangle.points[i], window, materials);
    glTexCoord2f(triangle.textures[i]->x, triangle.textures[i]->y);
    glVertex3f(triangle.points[i]->x / window._proportion / window._zoom,
               triangle.points[i]->y / window._zoom,
               triangle.points[i]->z / window._zoom);
  }
  glEnd();
}

void Models::drawLines(WindowManager &window, Triangles &triangle,
                       vector<Material> &materials) {
  glBegin(GL_LINES);
  for (int i = 0; i < 3; i++) {
    Shader(triangle.points[i], window, materials);
    glTexCoord2f(triangle.textures[i]->x, triangle.textures[i]->y);
    glVertex3f(triangle.points[i]->x / window._proportion / window._zoom,
               triangle.points[i]->y / window._zoom,
               triangle.points[i]->z / window._zoom);
    glVertex3f(triangle.points[(i + 1) % 3]->x / window._proportion /
                   window._zoom,
               triangle.points[(i + 1) % 3]->y / window._zoom,
               triangle.points[(i + 1) % 3]->z / window._zoom);
  }
  glEnd();
}

void Models::drawTriangles(WindowManager &window, vector<Material> &materials) {
  if (window._mode % 3 == 0) {
    for (Triangles &it : _triangles)
      drawTriangle(window, it, materials);
  } else if (window._mode % 3 == 1) {
    for (Triangles &it : _triangles)
      drawPoints(window, it, materials);
  } else {
    for (Triangles &it : _triangles)
      drawLines(window, it, materials);
  }
}

void renderLoop(WindowManager &window, vector<Models> &models,
                vector<Material> &materials) {
  while (!glfwWindowShouldClose(window._window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    window._material = &materials[models[window._currentWindow % models.size()]
                                      ._currentTexture %
                                  materials.size()];
    if (materials[models[window._currentWindow % models.size()]
                      ._currentTexture %
                  materials.size()]
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