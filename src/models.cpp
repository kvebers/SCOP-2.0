#include "../includes/models.hpp"
#include "../includes/utils.hpp"
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
  std::cout << _points[0]->x << _points[0]->y << _points[0]->z << endl;
}

//@todo Adding more textures can be also done in this function, but I guess I
// will
// make a seperate UV map function for later

void Models::processPoint(std::string &point1, std::string &point2,
                          std::string &point3, Triangles &tri,
                          vector<Vec3 *> &vec) {
  tri.points[0] = vec[std::stoi(point1) - 1];
  tri.points[1] = vec[std::stoi(point2) - 1];
  tri.points[2] = vec[std::stoi(point3) - 1];
  // // std::cout << vec[std::stoi(point1) - 1]->x << " " << tri.points[0]->x <<
  // endl;
  // // std::cout << tri.points[0]->x;
}

// @todo write a way of adding in textures from the compiler
void Models::createTriangle(std::string &point1, std::string &point2,
                            std::string &point3) {
  Triangles tri;
  processPoint(point1, point2, point3, tri, _points);
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

Models::Models(string objectName) : _objectName(objectName) {
  _initState = check_parsing(objectName, ".obj");
  if (_initState < 0)
    return;
  readPoints();
  readTriangles();
  _initState = 0;
}
