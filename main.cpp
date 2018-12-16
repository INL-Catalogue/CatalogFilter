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

  std::vector<node> node_vector;

  std::string line;
  while (std::getline(ifs, line)) {
    vector<int>         a;
    std::vector<string> strvec = split(line, ',');
    for (int i = 0; i < strvec.size(); i++) {
      a.push_back(std::stoi(strvec.at(i)));
    }
    for (int i = 0; i < a.size(); i++) {
      if (node_vector.size() != 0) {
        // 2番目以降の要素の追加
        for (int j = 0; j < node_vector.size(); j++) {
          if (a.at(i) == node_vector.at(j).id) {
            // a(i)がノード配列の既存idと一致した場合
            for (int k = 0; k < a.size(); k++) {
              if (k == i) continue;
              for (int l = 0; l < node_vector.at(j).neighbor.size(); l++) {
                if (a.at(k) == node_vector.at(j).neighbor.at(l).id) {
                  // a(k)がneighborの既存idと一致した場合
                  node_vector.at(j).neighbor.at(l).weight++;
                  break;
                } else if (l == node_vector.at(j).neighbor.size() - 1) {
                  // a(k)がneighborに存在しないidの場合
                  struct neighbor ng;
                  ng.id     = a.at(k);
                  ng.weight = 1;
                  node_vector.at(j).neighbor.push_back(ng);
                }
              }
            }
          } else if (j == node_vector.size() - 1) {
            // a(i)がノード配列に存在しないidだった場合
            struct node     n;
            struct neighbor ng;
            n.id = a.at(i);
            for (int k = 0; k < a.size(); k++) {
              if (i == k) continue;
              ng.id     = a.at(k);
              ng.weight = 1;
              n.neighbor.push_back(ng);
            }
            node_vector.push_back(n);
          }
        }
      } else if (node_vector.size() == 0) {
        // 1番最初の要素の追加
        struct node n;
        n.id = a.at(0);
        node_vector.push_back(n);
        for (int i = 1; i < a.size(); i++) {
          struct neighbor ng;
          ng.id     = a.at(i);
          ng.weight = 1;
          node_vector.at(0).neighbor.push_back(ng);
        }
      }
    }
  }
  ifs.close();

  print_vector(node_vector);

  cout << node_vector.at(1).neighbor.at(0).id << endl;

  return 0;
}