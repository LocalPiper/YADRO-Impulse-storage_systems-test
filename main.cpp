#include "box.hpp"
#include "interpreter.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " inputFile" << std::endl;
    return -1;
  }
  std::ifstream infile(argv[1]);
  std::string line;
  std::vector<std::string> lines;
  if (infile.is_open()) {
    while (getline(infile, line)) {
      lines.push_back(line);
    }
    infile.close();
  } else {
    std::cerr << "Error: couldn't open file " << argv[1] << std::endl;
    return -1;
  }
  DataBox data;
  try {
    data = parse(lines);
  } catch (const ValidationError &err) {
    std::cerr << err.what() << std::endl;
    return -1;
  }

  interpret(data);

  return 0;
}
