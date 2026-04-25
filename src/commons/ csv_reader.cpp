#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>

class CsvReader {
public:
  std::string filename = "";

  std::vector<std::vector<std::string>> read_csv(std::string filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
      std::cerr << "Failed to open file" << std::endl;
      return data;
    }

    std::string line;
    while (std::getline(file, line)) {

      std::string cell;
      std::vector<std::string> row;

      std::stringstream ss(line);
      while (std::getline(ss, cell, ',')) {
        row.push_back(cell);
      }
      data.push_back(row);
    }

    return data;
  }
};

int main() {
  CsvReader csr;
  auto data = csr.read_csv("example.csv");

  for (const auto &row : data) {
    for (const auto &cell : row) {
      std::cout << cell << '\t';
    }
    std::cout << std::endl;
  }
}
