#include <fstream>
#include <iostream>
#include <math.h>
#include <string_view>
#include <vector>

class CsvReader {
public:
  std::string filename = "";

  std::vector<std::string_view> parse_row(std::string_view &row) {
    std::vector<std::string_view> result;
    std::string temp;
    size_t start = 0;
    bool isQuote = false;

    for (size_t i = 0; row.length(); i++) {
      if (row[i] == ',' && isQuote == true) {
        result.emplace_back(row.substr(start, i - start));
        start = i + 1;
      } else if (row[i] == '"') {
        isQuote = !isQuote;
      }
    }
    return result;
  }

  std::vector<std::vector<std::string_view>> read_csv(std::string filename) {
    std::vector<std::vector<std::string_view>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
      std::cerr << "Failed to open file" << std::endl;
      return data;
    }

    std::string line;
    while (std::getline(file, line)) {
      data.push_back(parse_row(line));
    }

    file.close();
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
