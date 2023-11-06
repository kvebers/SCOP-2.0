#include "../includes/models.hpp"
#include "../includes/stb_image.hpp"

int main(int argc, char **argv) {
  vector<Models> models;
  for (int i = 1; i < argc; i++) {
    Models model((string(argv[i])));
    models.push_back(model);
  }

  return 0;
}