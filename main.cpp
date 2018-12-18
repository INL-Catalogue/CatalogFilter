#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "include/CatalogFilter.h"

using namespace std;

int main() {
  // csvファイルの読み込み
  std::ifstream ifs("data.csv");
  ifs.is_open();

  std::string line;
  while (std::getline(ifs, line)) {
    vector<int>         a;
    std::vector<string> strvec = split(line, ',');
    for (int i = 0; i < strvec.size(); i++) {
      a.push_back(std::stoi(strvec.at(i)));
      std::cout << "[" << i << "]: " << a.at(i) << ", ";
    }
    cout << endl;
  }
  ifs.close();

  return 0;
}