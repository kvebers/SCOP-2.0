#include "../includes/models.hpp"

int main(int argc, char **argv) {
  vector<Models> models;
  for (int i = 1; i < argc; i++) {
    Models model((string(argv[i])));
    if (model._initState == 0)
      models.push_back(model);
    else
      std::cerr << "Error with model " << argv[i] << endl;
  }
  if (models.size() == 0) {
    std::cerr << "No Model Was loaded sucessfuly" << std::endl;
    return 1;
  }
  glfwInit();
  WindowManager window;
  vector<Material> materials;
  addMaterials(materials);
  draw(models, window, materials);
  system("leaks scop");
  return 0;
}