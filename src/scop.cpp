#include "../includes/models.hpp"

int main(int argc, char **argv) {
  glfwInit();
  vector<Models> models;
  for (int i = 1; i < argc; i++) {
    Models model((string(argv[i])));
    if (model._initState == 0)
      models.push_back(model);
  }
  if (models.size() == 0)
    std::cerr << "No Model Was loaded sucessfuly" << std::endl;
  WindowManager window;
  vector<Material> materials;
  addMaterials(materials);
  draw(models, window, materials);
  system("leaks scop");
  return 0;
}