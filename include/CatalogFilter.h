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

// stringを","で区切ってvectorに保存する関数
std::vector<string> split(std::string &input, char delimiter) {
  std::istringstream  stream(input);
  std::string         field;
  std::vector<string> result;
  while (std::getline(stream, field, delimiter)) {
    result.push_back(field);
  }
  return result;
}

// ノードデータを出力する関数
void print(struct node node) {
  std::cout << "id = " << node.id << endl;
  std::cout << "neighbor: ";
  for (int i = 0; i < node.neighbor.size(); i++) {
    if (i == node.neighbor.size() - 1)
      std::cout << node.neighbor.at(i).id << endl;
    else
      std::cout << node.neighbor.at(i).id << ", ";
  }
  std::cout << "weight:   ";
  for (int i = 0; i < node.neighbor.size(); i++) {
    if (i == node.neighbor.size() - 1)
      std::cout << node.neighbor.at(i).weight << endl;
    else
      std::cout << node.neighbor.at(i).weight << ", ";
  }
}

// ノード配列の全てのノードデータを出力する関数
void print_vector(std::vector<node> node_vector) {
  for (int j = 0; j < node_vector.size(); j++) {
    print(node_vector.at(j));
  }
}

// 既存のノードかどうか判定する関数（返り値は一致したindex or
// 一致しない場合は-1）
int node_check(int a, std::vector<node> node_vector) {
  for (int i = 0; i < node_vector.size(); i++) {
    if (a == node_vector.at(i).id) return i;
  }
  return -1;
}

// 既存の隣接ノードかどうか判定する関数（返り値は一致した場合はindex or
// 一致しない場合は-1）
int neighbor_check(int a, struct node node) {
  for (int i = 0; i < node.neighbor.size(); i++) {
    if (a == node.neighbor.at(i).id) return i;
  }
  return -1;
}

// score配列とaccum配列を出力する関数
void print_score(std::vector<node> node_vector, double score[],
                 double accum[]) {
  cout << "  id  |";
  for (int i = 0; i < node_vector.size(); i++) {
    if (i == node_vector.size() - 1)
      cout << "  " << node_vector.at(i).id << "  |" << endl;
    else
      cout << "  " << node_vector.at(i).id << "  |";
  }
  cout << "score |";
  for (int i = 0; i < node_vector.size(); i++) {
    if (i == node_vector.size() - 1)
      cout << " " << score[i] << " |" << endl;
    else
      cout << " " << score[i] << " |";
  }
  cout << "accum |";
  for (int i = 0; i < node_vector.size(); i++) {
    if (i == node_vector.size() - 1)
      cout << "  " << accum[i] << "  |" << endl;
    else
      cout << "  " << accum[i] << "  |";
  }
}

void generate_edge(std::vector<node> node_vector, double *edge) {
  for (int i = 0; i < node_vector.size(); i++) {
    double element = 1.0 / (double)node_vector.at(i).neighbor.size();
    for (int j = 0; j < node_vector.size(); j++) {
      int k = neighbor_check(node_vector.at(j).id, node_vector.at(i));
      // cout << "k = " << k << endl;
      if (k != -1) *(edge + i * node_vector.size() + j) = element;
    }
  }
}

void print_edge(std::vector<node> node_vector, double *edge) {
  for (int i = 0; i < node_vector.size(); i++) {
    cout << "| " << node_vector.at(i).id << " |";
    for (int j = 0; j < node_vector.size(); j++) {
      cout << " " << *(edge + i * node_vector.size() + j) << " ";
    }
    cout << endl;
  }
}