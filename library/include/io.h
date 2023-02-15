#include <iostream>
#include <fstream>
#include <sstream>
#include "Vector.h"
#include <string>

using namespace phoenix;


template<typename T>
void ReadFileToMatrix(const std::string& filename, Matrix<T>& matrix) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  std::string line;
  std::vector<double> values;
  int rows = 0, cols, col = 0;

  while (std::getline(file, line)) {
    std::stringstream line_stream(line);
    double value;
    col = 0;
    while (line_stream >> value) {
      if (col == 0) {
        cols++;
      }
      values.push_back(value);
      col++;
    }
    ++rows;
  }

 std::cout<< rows<< " "<<col <<std::endl;
  matrix = Matrix<T>(rows, col);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < col; ++j) {
      matrix(i, j) = values[i * col + j];
    }
  }

  file.close();
}

