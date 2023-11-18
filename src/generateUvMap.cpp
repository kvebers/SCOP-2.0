#include "../includes/models.hpp"
#include "../includes/utils.hpp"
#include <cmath>
#include <map>

float calculateDistance(Triangles &it, int p1, int p2) {
  return (sqrt(pow(it.points[p1]->x - it.points[p2]->x, 2) +
               pow(it.points[p1]->y - it.points[p2]->y, 2) +
               pow(it.points[p1]->z - it.points[p2]->z, 2)));
}

void Models::createTexturePoints() {
  if (_uvMap == false) {
    for (auto &it : _vt)
      delete it;
  }
  _vt.clear();
  for (auto it : _points) {
    (void)it;
    Vec3 *point = new Vec3(std::nanf("1"), std::nanf("1"), std::nanf("1"));
    _vt.push_back(point);
  }
  for (auto &it : _triangles) {
    it.textures[0] = _vt[it.connections[0]];
    it.textures[1] = _vt[it.connections[1]];
    it.textures[2] = _vt[it.connections[2]];
  }
}

int checkIfNanf(Triangles &tri) {
  int cnt = 0;
  for (int i = 0; i < 3; i++) {
    if (std::isnan(tri.textures[i]->x) && std::isnan(tri.textures[i]->y) &&
        std::isnan(tri.textures[i]->z))
      cnt++;
  }
  return cnt;
}

void PlotThirdPoint(Triangles &it, int point1, int point2, int targetPoint) {
  float distancePT1 = calculateDistance(it, point1, targetPoint);
  float distancePT2 = calculateDistance(it, point2, targetPoint);
  float distancePT1PT2 = calculateDistance(it, point2, point1);
  if (distancePT1PT2 == 0) {
    cout << "here" << endl;
    distancePT1PT2 = 1;
  }
  if (distancePT1PT2 > distancePT1 + distancePT2) {
    it.textures[targetPoint]->x = 0;
    it.textures[targetPoint]->y = 0;
    it.textures[targetPoint]->z = 0;
    return;
  }
  float a = (distancePT1 * distancePT1 - distancePT2 * distancePT2 +
             distancePT1PT2 * distancePT1PT2) /
            (2 * distancePT1PT2);
  float h = sqrt(distancePT1 * distancePT1 - a * a);
  it.textures[targetPoint]->x =
      it.textures[point1]->x +
      a * (it.textures[point2]->x - it.textures[point1]->x) / distancePT1PT2 +
      h * (it.textures[point2]->y - it.textures[point1]->y) / distancePT1PT2;
  it.textures[targetPoint]->y =
      it.textures[point1]->y +
      a * (it.textures[point2]->y - it.textures[point1]->y) / distancePT1PT2 -
      h * (it.textures[point2]->x - it.textures[point1]->x) / distancePT1PT2;
  it.textures[targetPoint]->z = 0;
}

void createTheTriangle(Triangles &it) {
  it.textures[0]->x = 0;
  it.textures[0]->y = 0;
  it.textures[0]->z = 0;
  it.textures[1]->x = calculateDistance(it, 0, 1);
  it.textures[1]->y = 0;
  it.textures[1]->z = 0;
  PlotThirdPoint(it, 0, 1, 2);
}

void findThirdPoint(Triangles &it, int *point1, int *point2, int *targetPoint) {
  if (std::isnan(it.textures[0]->x) && std::isnan(it.textures[0]->y) &&
      std::isnan(it.textures[0]->z)) {
    *point1 = 1;
    *point2 = 2;
    *targetPoint = 0;
  } else if (std::isnan(it.textures[1]->x) && std::isnan(it.textures[1]->y) &&
             std::isnan(it.textures[1]->z)) {
    *point1 = 0;
    *point2 = 2;
    *targetPoint = 1;
  } else {
    *point1 = 0;
    *point2 = 1;
    *targetPoint = 2;
  }
}

void createTriangleFrom2Points(Triangles &it) {
  int point1;
  int point2;
  int targetPoint;
  findThirdPoint(it, &point1, &point2, &targetPoint);
  PlotThirdPoint(it, point1, point2, targetPoint);
}

void Models::generateUvMap() {
  createTexturePoints();
  int plotedPoints = _vt.size();
  bool PointsRendered = false;
  cout << plotedPoints << endl;
  while (PointsRendered != true) {
    for (auto &it : _triangles) {
      if (checkIfNanf(it) == 3) {
        createTheTriangle(it);
        cout << " Seperate Renders object " << plotedPoints << endl;
        plotedPoints--;
        break;
      }
    }
    int changeTracker = plotedPoints + 1;
    while (changeTracker != plotedPoints) {
      changeTracker = plotedPoints;
      for (auto &it : _triangles) {
        if (checkIfNanf(it) == 1) {
          createTriangleFrom2Points(it);
          plotedPoints--;
        }
      }
    }
    unsigned long cnt = 0;
    for (auto &it : _triangles) {
      if (checkIfNanf(it) != 0)
        break;
      else
        cnt++;
    }
    if (cnt == _triangles.size())
      PointsRendered = true;
  }
}