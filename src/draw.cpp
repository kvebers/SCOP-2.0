#include "../includes/models.hpp"
#include <vector>

void Models::drawTriangle(WindowManager &window, Triangles &triangle,
                          vector<Material> &materials) {
  (void)window;
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 3; i++) {
    Shader(triangle.points[i], window, materials);
    glVertex3f(triangle.points[i]->x / window._proportion,
               triangle.points[i]->y, triangle.points[i]->z);
  }
  glEnd();
}

void Models::drawTriangles(WindowManager &window, vector<Material> &materials) {
  for (Triangles &it : _triangles)
    drawTriangle(window, it, materials);
}

void Models::rotateShape(WindowManager &window) {
  if (window._isRotating == false)
    return;
  float rotateXRad = window._rotateX * M_PI / 180.0f;
  float rotateYRad = window._rotateY * M_PI / 180.0f;
  float cosX = cos(rotateXRad);
  float sinX = sin(rotateXRad);
  float cosY = cos(rotateYRad);
  float sinY = sin(rotateYRad);
  for (Vec3 *point : _points) {
    float yNew = point->y * cosX - point->z * sinX;
    float zNew = point->y * sinX + point->z * cosX;
    point->y = yNew;
    point->z = zNew;
    float xNew = point->x * cosY + point->z * sinY;
    zNew = -point->x * sinY + point->z * cosY;
    point->x = xNew;
    point->z = zNew;
  }
}

void Models::moveShape(WindowManager &window) {
  if (window._isMoving == false)
    return;

  for (auto &it : _points) {
    Vec3 &points = *it;
    points.x += window._rotateY / 100;
    points.y -= window._rotateX / 100;
  }
}

void Models::calculateMedium() {
  for (auto it = _triangles.begin(); it != _triangles.end(); it++) {
    Triangles tri = *it;
    tri.avg = (tri.points[0]->z + tri.points[1]->z + tri.points[2]->z) / 3;
    it->avg = tri.avg;
  }
  std::sort(
      _triangles.begin(), _triangles.end(),
      [](const Triangles &a, const Triangles &b) { return a.avg < b.avg; });
}

void Models::updateShape(WindowManager &window) {
  if (window._ceneterObject == true) {
    window._ceneterObject = false;
    centerObject();
  }
  rotateShape(window);
  moveShape(window);
  calculateMedium();
  if (window._rotateX != 0 || window._rotateY != 0)
    calculateMedium();
  window._rotateX = 0;
  window._rotateY = 0;
}

void renderLoop(WindowManager &window, vector<Models> &models,
                vector<Material> &materials) {
  while (!glfwWindowShouldClose(window._window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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