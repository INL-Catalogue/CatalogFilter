#include <iostream>
#include <string>
#include <vector>

struct neighbor {
  int    id;
  double weight;
};

struct node {
  // mapのときのid(key)と一致させるようにする
  int                   id;
  std::vector<neighbor> neighbor;
};
