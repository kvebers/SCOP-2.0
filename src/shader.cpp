#include "../includes/models.hpp"

Vec3 Magnitude(Vec3 point) {
  Vec3 magnitude(0, 0, 0);
  float magHelper =
      sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
  if (magHelper == 0) {
    return magnitude;
  } else {
    magnitude.x = point.x / magHelper;
    magnitude.y = point.y / magHelper;
    magnitude.z = point.z / magHelper;
  }
  return magnitude;
}

Vec3 Multiply(Vec3 first, Vec3 other) {
  Vec3 result(0, 0, 0);
  result.x = first.x * other.x;
  result.y = first.y * other.y;
  result.z = first.z * other.z;
  return result;
}

Vec3 Max(Vec3 first, Vec3 other) {
  Vec3 valToRet(0, 0, 0);
  valToRet.x = std::max(first.x, other.x);
  valToRet.y = std::max(first.y, other.y);
  valToRet.z = std::max(first.z, other.z);
  return valToRet;
}

Vec3 Sub(Vec3 first, Vec3 other) {
  Vec3 valToReturn(0, 0, 0);
  valToReturn.x = first.x - other.x;
  valToReturn.y = first.y - other.y;
  valToReturn.z = first.z - other.z;
  return valToReturn;
}

Vec3 Pow(Vec3 first, float other) {
  Vec3 valToReturn(0, 0, 0);
  valToReturn.x = (first.x == 0 && other <= 0) ? 0 : pow(first.x, other);
  valToReturn.y = (first.y == 0 && other <= 0) ? 0 : pow(first.y, other);
  valToReturn.z = (first.z == 0 && other <= 0) ? 0 : pow(first.z, other);
  return valToReturn;
}

Vec3 Add(Vec3 first, Vec3 other) {
  Vec3 valToReturn(0, 0, 0);
  valToReturn.x = first.x + other.x;
  valToReturn.y = first.y + other.y;
  valToReturn.z = first.z + other.z;
  return valToReturn;
}

Vec3 Normalize(Vec3 first) {
  Vec3 valToReturn(0, 0, 0);
  float division =
      sqrt(first.x * first.x + first.y * first.y + first.z * first.z);
  if (division == 0)
    return valToReturn;
  else {
    valToReturn.x = first.x / division;
    valToReturn.y = first.y / division;
    valToReturn.z = first.z / division;
  }
  return valToReturn;
}

Vec3 Dot(Vec3 first, Vec3 other) {
  Vec3 valToReturn(0, 0, 0);
  float value = first.x * other.x + first.y * other.y + first.z * other.z;
  valToReturn.x = value;
  valToReturn.y = value;
  valToReturn.z = value;
  return valToReturn;
}

Vec3 Reflect(const Vec3 &incoming, const Vec3 &normal) {
  Vec3 twos(2, 2, 2);
  Vec3 dotProd = Dot(incoming, normal);
  return Sub(incoming, Multiply(normal, Multiply(twos, dotProd)));
}

void Models::Shader(Vec3 *point, WindowManager &window) {
  Vec3 def(0, 0, 0);
  Vec3 normal(0, 1, 0);
  Vec3 lightDir = Normalize(Sub(_lightData, *point));
  Vec3 viewDir = Normalize(Sub(_viewPos, *point));
  Vec3 ambient = Multiply(_material[modifier].Ka, _lightColor);
  Vec3 diffIntensity = Max(Dot(normal, lightDir), def);
  Vec3 diffHelper = Multiply(_material[modifier].Kd, _lightColor);
  Vec3 diffuse = Multiply(diffHelper, diffIntensity);
  Vec3 reflectDir = Reflect(Sub(def, lightDir), normal);
  Vec3 specIntensity =
      Pow(Max(Dot(viewDir, reflectDir), def), _material[modifier].Ns);
  Vec3 specular =
      Multiply(Multiply(_material[modifier].Ks, _lightColor), specIntensity);
  Vec3 result = Add(ambient, Add(diffuse, specular));
  glColor4f(result.x, result.y, result.z, _material[modifier].d);
}
