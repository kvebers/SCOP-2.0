#include "../includes/utils.hpp"
#include "../includes/models.hpp"

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
