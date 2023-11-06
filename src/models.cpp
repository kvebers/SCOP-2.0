#include "../includes/models.hpp"
#include "../includes/utils.hpp"

void Models::addPoint(string line, vector<Vec3> &vec) {
  std::istringstream iss(line);
  string prefix;
  float x, y, z;
  iss >> prefix;
  iss >> x >> y >> z;
  Vec3 vector(x, y, z);
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

void Models::readTriangles() {
  std::ifstream obj(_objectName);
  std::string line;
  while (std::getline(obj, line)) {
    if (line.substr(0, 2).compare("f ") == 0) {

      Triangles tri;
      tri.po
    }
  }
  obj.close();
}

Models::Models(string objectName) : _objectName(objectName) {
  _initState = check_parsing(objectName, ".obj");
  if (_initState < 0)
    return;
  readPoints();
  readTriangles();
  _initState = 0;
}
