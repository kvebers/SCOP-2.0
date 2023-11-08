#include "../includes/models.hpp"
#include <fstream>

Material SetupDefaultMaterial() {
  Material mat;
  mat.Ka.x = 0.0f;
  mat.Ka.z = 0.0f;
  mat.Ka.y = 0.0f;
  mat.Ks.x = 0.0f;
  mat.Ks.z = 0.0f;
  mat.Ks.y = 0.0f;
  mat.Kd.x = 0.0f;
  mat.Kd.z = 0.0f;
  mat.Kd.y = 0.0f;
  mat.d = 1.0f;
  mat.illum = 2.0f;
  mat.Ns = 100;
  mat.Ni = 0;
  return mat;
}

void addMaterials(vector<Material> &materials) {
  std::ifstream file("mtl/color.mtl");

  if (!file.is_open()) {
    std::cerr << "Filed to Open the MTL file " << std::endl;
    return;
  }
  try {
    Material material = SetupDefaultMaterial();
    std::string line;
    while (getline(file, line)) {
      std::string prefix;
      std::istringstream iss(line);
      iss >> prefix;
      if (prefix == "Ns")
        material.Ns = std::stof(line.substr(3));
      else if (prefix == "Ka") {
        std::string ka1, ka2, ka3;
        iss >> ka1 >> ka2 >> ka3;
        material.Ka.x = std::stof(ka1);
        material.Ka.y = std::stof(ka2);
        material.Ka.z = std::stof(ka3);
      } else if (prefix == "Kd") {
        std::string kd1, kd2, kd3;
        iss >> kd1 >> kd2 >> kd3;
        material.Kd.x = std::stof(kd1);
        material.Kd.y = std::stof(kd2);
        material.Kd.z = std::stof(kd3);
      } else if (prefix == "Ks") {
        std::string ks1, ks2, ks3;
        iss >> ks1 >> ks2 >> ks3;
        material.Ks.x = std::stof(ks1);
        material.Ks.y = std::stof(ks2);
        material.Ks.z = std::stof(ks3);
      } else if (prefix == "Ni") {
        std::string ni;
        iss >> ni;
        material.Ni = std::stof(ni);
      } else if (prefix == "d") {
        std::string d;
        iss >> d;
        material.d = std::stof(d);
      } else if (prefix == "illum") {
        std::string illum;
        iss >> illum;
        material.illum = std::stof(illum);
      }
    }
    materials.push_back(material);
  } catch (const std::exception &error) {
    std::cerr << "Error invalid material: " << error.what() << std::endl;
  }
}