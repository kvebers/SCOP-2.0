#include "../includes/utils.hpp"
#include "../includes/models.hpp"
#include <sys/stat.h>

int check_parsing(string &argv, string comp) {
  std::string parsed = std::string(argv);
  if (parsed.length() < 4) {
    std::cerr << "Not an " << comp << " file: " << parsed << std::endl;
    return -1;
  }
  if (parsed.substr(parsed.length() - 4) != comp) {
    std::cerr << "Not an " << comp << " file: " << parsed << std::endl;
    return -1;
  }
  std::ifstream file(parsed);
  if (!file.is_open()) {
    std::cerr << "Failed to open" << comp << " file: " << parsed << std::endl;
    return -1;
  }
  file.close();
  return 0;
}

bool fileExists(const std::string &name) {
  std::ifstream file(name.c_str());
  return file.good();
}

string replaceModelWithPath(string modelPath) {
  size_t laspos = modelPath.find_last_of("/");
  size_t dotPos = modelPath.rfind(".obj");
  if (laspos != string::npos && dotPos != string::npos) {
    string fname = modelPath.substr(laspos + 1, dotPos - laspos - 1);
    string texturePath = "textures/" + fname + ".jpg";
    if (fileExists(texturePath))
      return texturePath;
  }
  return "textures/uv.jpg";
}
