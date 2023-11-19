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

void Models::normTexture() {
  float maxX = 0, maxY = 0, minX = 0, minY = 0;
  for (auto &it : _vt) {
    if (maxX < it->x)
      maxX = it->x;
    if (maxY < it->y)
      maxY = it->y;
    if (minX > it->x)
      minX = it->x;
    if (minY > it->y)
      minY = it->y;
  }
  float delta = maxX - minX;
  if (maxY - minY > delta)
    delta = maxY - minY;
  for (auto &it : _vt) {
    it->x = (it->x - minX) / delta;
    it->y = (it->y - minY) / delta;
  }
}

void convert_xyz_to_cube_uv(float x, float y, float z, Vec3 *texture) {
  float absX = fabs(x);
  float absY = fabs(y);
  float absZ = fabs(z);
  int isXPositive = x > 0 ? 1 : 0;
  int isYPositive = y > 0 ? 1 : 0;
  int isZPositive = z > 0 ? 1 : 0;
  float maxAxis, uc, vc;
  if (isXPositive && absX >= absY && absX >= absZ) {
    maxAxis = absX;
    uc = -z;
    vc = y;
  }
  if (!isXPositive && absX >= absY && absX >= absZ) {
    maxAxis = absX;
    uc = z;
    vc = y;
  }
  if (isYPositive && absY >= absX && absY >= absZ) {
    maxAxis = absY;
    uc = x;
    vc = -z;
  }
  if (!isYPositive && absY >= absX && absY >= absZ) {
    maxAxis = absY;
    uc = x;
    vc = z;
  }
  if (isZPositive && absZ >= absX && absZ >= absY) {
    maxAxis = absZ;
    uc = x;
    vc = y;
  }
  if (!isZPositive && absZ >= absX && absZ >= absY) {
    maxAxis = absZ;
    uc = -x;
    vc = y;
  }
  float u = 0.5f * (uc / maxAxis + 1.0f);
  float v = 0.5f * (vc / maxAxis + 1.0f);
  texture->x = u;
  texture->y = v;
  texture->z = 0;
}

void Models::generateUvMap() {
  createTexturePoints();
  for (unsigned long i = 0; i < _vt.size(); i++) {
    convert_xyz_to_cube_uv(_points[i]->x, _points[i]->y, _points[i]->z, _vt[i]);
  }
  normTexture();
}