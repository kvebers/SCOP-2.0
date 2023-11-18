#include "../includes/models.hpp"
#include "../includes/utils.hpp"
#include <algorithm>
#include <string>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "../includes/stb_image.hpp"

Models::~Models() {
  // for (Vec3 *vector : _points) {
  //   delete vector;
  // }
  // _points.clear();
}

void Models::addPoint(string line, vector<Vec3 *> &vec) {
  std::istringstream iss(line);
  string prefix;
  float x, y, z;
  iss >> prefix;
  iss >> x >> y >> z;
  if (prefix == "vt") {
    Vec3 *vector = new Vec3(x, 1 - y, z);
    vec.push_back(vector);
  } else {
    Vec3 *vector = new Vec3(x, y, z);
    vec.push_back(vector);
  }
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
  tri.connections[0] = std::stoi(point1) - 1;
  tri.connections[1] = std::stoi(point2) - 1;
  tri.connections[2] = std::stoi(point3) - 1;
}

void Models::processTexture(std::string &point1, std::string &point2,
                            std::string &point3, Triangles &tri,
                            vector<Vec3 *> &vec) {
  tri.textures[0] = vec[std::stoi(point1) - 1];
  tri.textures[1] = vec[std::stoi(point2) - 1];
  tri.textures[2] = vec[std::stoi(point3) - 1];
}

// @todo write a way of adding in textures from the compiler

void Models::createTriangle(std::string &point1, std::string &point2,
                            std::string &point3) {
  Triangles tri;
  processPoint(point1, point2, point3, tri, _points);
  if (_uvMap == true) {
    if (point1.find_first_of("/") != std::string::npos &&
        point2.find_first_of("/") != std::string::npos &&
        point3.find_first_of("/") != std::string::npos) {
      size_t subPoint1 = point1.find_first_of("/");
      size_t subPoint2 = point2.find_first_of("/");
      size_t subPoint3 = point3.find_first_of("/");
      string substring1 = point1.substr(subPoint1 + 1);
      string substring2 = point2.substr(subPoint2 + 1);
      string substring3 = point3.substr(subPoint3 + 1);
      processTexture(substring1, substring2, substring3, tri, _vt);
    } else
      _uvMap = false;
  }
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
          createTriangle(point1, point3, point2);
        else {
          createTriangle(point1, point4, point3);
          createTriangle(point1, point3, point2);
        }
      }
    }
  }
  obj.close();
  if (_uvMap == false) {
    cout << _objectName << ": Does not have a builtin UVMap " << endl;
    generateUvMap();
  } else
    cout << _objectName << ": Has a builtin UVMap " << endl;
  cout << _objectName << " has " << error << " errors" << endl;
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

void Models::loadTexture() {
  int width;
  int height;
  int channels;
  GLint maxTextureSize;
  string path = replaceModelWithPath(_objectName);
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (data) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    if (width > maxTextureSize || height > maxTextureSize) {
      std::cerr << "Texture to big" << std::endl;
      exit(127);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_image_free(data);
  } else {
    std::cerr << "Error Loading the image" << std::endl;
    return;
  }
  cout << "Texture " << path << " has been loaded for " << _objectName << endl;
}

Models::Models(string objectName) : _objectName(objectName) {
  _uvMap = true;
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
  if (window._rotateX != 0 || window._rotateY != 0)
    calculateMedium();
  window._rotateX = 0;
  window._rotateY = 0;
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
