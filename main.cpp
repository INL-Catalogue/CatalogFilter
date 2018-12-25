#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "include/CatalogFilter.h"

using namespace std;

int main() {
  //////////////////////////
  //  csvファイルの読み込み  //
  //////////////////////////

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
        if (node_check(a.at(i), node_vector) == -1) {
          // 新出のノードの場合
          struct node n;
          n.id = a.at(i);
          struct neighbor ng;
          for (int j = 0; j < a.size(); j++) {
            if (j != i) {
              ng.id     = a.at(j);
              ng.weight = 1;
              n.neighbor.push_back(ng);
            }
          }
          node_vector.push_back(n);
        } else {
          // 既存のノードの場合
          int j = node_check(a.at(i), node_vector);
          for (int k = 0; k < a.size(); k++) {
            if (k != i) {
              int l = neighbor_check(a.at(k), node_vector.at(j));
              if (l == -1) {
                // 新出のneighborの場合
                struct neighbor ng;
                ng.id     = a.at(k);
                ng.weight = 1;
                node_vector.at(j).neighbor.push_back(ng);
              } else {
                // 既存のneighborの場合
                node_vector.at(j).neighbor.at(l).weight++;
              }
            }
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
  cout << endl;

  //////////////////////
  //  スコア配列の生成  //
  /////////////////////

  double score[node_vector.size()];
  double accum[node_vector.size()];

  for (int i = 0; i < node_vector.size(); i++) {
    score[i] = 100.0;
    accum[i] = 0.0;
  }

  print_score(node_vector, score, accum);
  cout << endl;

  /////////////////////
  //  edge行列の生成  //
  ////////////////////

  double edge[node_vector.size()][node_vector.size()];
  for (int i = 0; i < node_vector.size(); i++) {
    for (int j = 0; j < node_vector.size(); j++) {
      edge[i][j] = 0;
    }
  }

  generate_edge(node_vector, &edge[0][0]);
  print_edge(node_vector, &edge[0][0]);

  return 0;
}