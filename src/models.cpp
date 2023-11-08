#include "../includes/models.hpp"
#include "../includes/utils.hpp"
#include <algorithm>
#include <string>
#include <vector>

Models::~Models() {
  // for (auto ptr : _points)
  //   delete ptr;
  // for (auto ptr : _vt)
  //   delete ptr;
}

void Models::addPoint(string line, vector<Vec3 *> &vec) {
  std::istringstream iss(line);
  string prefix;
  float x, y, z;
  iss >> prefix;
  iss >> x >> y >> z;
  Vec3 *vector = new Vec3(x, y, z);
  vec.push_back(vector);
}

void Models::readPoints() {
  std::ifstream obj(_objectName);
  std::string line;
  while (std::getline(obj, line)) {
    if (line.substr(0, 2).compare("v ") == 0)
      addPoint(line, _points);
    if (line.substr(0, 3).compare("vt ") == 0)
      addPoint(line, _vt);
  }
  obj.close();
}


void Models::processPoint(std::string &point1, std::string &point2,
                          std::string &point3, Triangles &tri,
                          vector<Vec3 *> &vec) {
  tri.points[0] = vec[std::stoi(point1) - 1];
  tri.points[1] = vec[std::stoi(point2) - 1];
  tri.points[2] = vec[std::stoi(point3) - 1];
}

// @todo write a way of adding in textures from the compiler





void Models::createTriangle(std::string &point1, std::string &point2,
                            std::string &point3) {
  Triangles tri;
  processPoint(point1, point2, point3, tri, _points);
  if (tri.points)



  _triangles.push_back(tri);
}

void Models::readTriangles() {
  std::ifstream obj(_objectName);
  std::string line;
  int error = 0;
  while (std::getline(obj, line)) {
    if (line.substr(0, 2).compare("f ") == 0) {
      std::istringstream iss(line);
      string prefix;
      string point1, point2, point3, point4;
      iss >> prefix;
      iss >> point1 >> point2;
      if (!(iss >> point3))
        error++;
      else {
        if (!(iss >> point4))
          createTriangle(point1, point2, point3);
        else {
          createTriangle(point1, point2, point3);
          createTriangle(point1, point3, point4);
        }
      }
    }
  }
  cout << _objectName << " has " << error << " errors" << endl;
  obj.close();
}

void Models::normalize() {
  Vec3 minPoint(0, 0, 0);
  Vec3 maxPoint(0, 0, 0);
  Vec3 delta(0, 0, 0);

  // Iterate through all the points to find the min and max
  for (const auto &point : _points) {
    if (point->x < minPoint.x)
      minPoint.x = point->x;
    if (point->y < minPoint.y)
      minPoint.y = point->y;
    if (point->z < minPoint.z)
      minPoint.z = point->z;
    if (point->x > maxPoint.x)
      maxPoint.x = point->x;
    if (point->y > maxPoint.y)
      maxPoint.y = point->y;
    if (point->z > maxPoint.z)
      maxPoint.z = point->z;
  }
  delta.x = (maxPoint.x - minPoint.x) / 2;
  delta.y = (maxPoint.y - minPoint.y) / 2;
  delta.z = (maxPoint.z - minPoint.z) / 2;
  float maxDelta = std::max(delta.x, delta.y);
  maxDelta = std::max(maxDelta, delta.z);
  for (auto &point : _points) {
    point->x /= maxDelta;
    point->y /= maxDelta;
    point->z /= maxDelta;
  }
}

Models::Models(string objectName) : _objectName(objectName) {
  _initState = check_parsing(objectName, ".obj");
  if (_initState < 0)
    return;
  readPoints();
  readTriangles();
  normalize();
  centerObject();
  _initState = 0;
}

void Models::centerObject() {
  int cnt = 0;
  float offsetX = 0;
  float offsetY = 0;
  float offsetZ = 0;
  for (auto &it : _points) {
    offsetX += it->x;
    offsetY += it->y;
    offsetZ += it->z;
    cnt++;
  }
  if (cnt == 0)
    return;
  offsetX /= cnt;
  offsetY /= cnt;
  offsetZ /= cnt;
  for (auto &it : _points) {
    it->x -= offsetX;
    it->y -= offsetY;
    it->z -= offsetZ;
  }
}