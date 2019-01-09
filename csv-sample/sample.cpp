#include <stdio.h>
#include <time.h>
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

int check(int id, vector<int> data);
int node_check(int id, vector<node> node_vector);
int neighbor_check(int a, struct node node);

int main() {
  int row;       // カタログ数
  int col;       // カタログ内のmaxコンテンツ数
  int node_num;  // 全体のノード数

  //////////////////////////////////////////////
  //  カタログ数とカタログ内のmaxコンテンツ数を指定  //
  //////////////////////////////////////////////

  cout << "row: ";
  cin >> row;
  cout << "col: ";
  cin >> col;
  cout << "node_num: ";
  cin >> node_num;

  /////////////////
  //  データ格納  //
  ////////////////

  ofstream ofs("data.csv");

  int node_id;   // ノードのid
  int content;   // その行のノード数
  int edge_num;  // エッジの本数

  std::vector<node> node_vector;

  srand((unsigned int)time(NULL));
  for (int i = 0; i < row; i++) {
    vector<int> data;  // 1行分のデータを格納する可変長配列
    content = rand() % col + 1;
    if (content >= 2) {
      for (int j = 0; j < content; j++) {
        node_id = rand() % node_num + 1;
        if (check(node_id, data)) {
          data.push_back(node_id);
          if (j != content - 1)
            ofs << node_id << ",";
          else
            ofs << node_id;
        } else
          j--;
      }
      ofs << endl;
      for (int i = 0; i < data.size(); i++) {
        if (node_vector.size() != 0) {
          // 2番目以降の要素の追加
          if (node_check(data.at(i), node_vector) == -1) {
            // 新出のノードの場合
            struct node n;
            n.id = data.at(i);
            struct neighbor ng;
            for (int j = 0; j < data.size(); j++) {
              if (j != i) {
                ng.id     = data.at(j);
                ng.weight = 1;
                n.neighbor.push_back(ng);
              }
            }
            node_vector.push_back(n);
          } else {
            // 既存のノードの場合
            int j = node_check(data.at(i), node_vector);
            for (int k = 0; k < data.size(); k++) {
              if (k != i) {
                int l = neighbor_check(data.at(k), node_vector.at(j));
                if (l == -1) {
                  // 新出のneighborの場合
                  struct neighbor ng;
                  ng.id     = data.at(k);
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
          n.id = data.at(0);
          node_vector.push_back(n);
          for (int i = 1; i < data.size(); i++) {
            struct neighbor ng;
            ng.id     = data.at(i);
            ng.weight = 1;
            node_vector.at(0).neighbor.push_back(ng);
          }
        }
      }
    } else
      i--;
  }

  ofs.close();

  for (int i = 0; i < node_vector.size(); i++) {
    edge_num += node_vector.at(i).neighbor.size();
    if (i == node_vector.size() - 1) edge_num /= 2;
  }

  cout << "node: " << node_vector.size() << endl;
  cout << "edge: " << edge_num << endl;
  cout << "catalog: " << row << endl;

  return 0;
}

int check(int id, vector<int> data) {
  for (int i = 0; i < data.size(); i++) {
    if (id == data.at(i)) return 0;
  }
  return 1;
}

int node_check(int a, std::vector<node> node_vector) {
  for (int i = 0; i < node_vector.size(); i++) {
    if (a == node_vector.at(i).id) return i;
  }
  return -1;
}

int neighbor_check(int a, struct node node) {
  for (int i = 0; i < node.neighbor.size(); i++) {
    if (a == node.neighbor.at(i).id) return i;
  }
  return -1;
}