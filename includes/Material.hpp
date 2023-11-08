#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "helper.hpp"
class Material {
public:
  float Ns;
  Vec3 Ka;
  Vec3 Kd;
  Vec3 Ks;
  float Ni;
  float d;
  int illum;
};

void addMaterials(vector<Material> &materials);

#endif