#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct neighbor {
  int    id;
  double weight;
};

struct node {
  // mapのときのid(key)と一致させるようにする
  int                   id;
  std::vector<neighbor> neighbor;
};

std::vector<string> split(std::string &input, char delimiter) {
  std::istringstream  stream(input);
  std::string         field;
  std::vector<string> result;
  while (std::getline(stream, field, delimiter)) {
    result.push_back(field);
  }
  return result;
}