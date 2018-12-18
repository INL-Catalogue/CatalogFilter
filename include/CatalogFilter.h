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
std::vector<string> split(std::string &input, char delimiter);

// ノードデータを出力する関数
void print(struct node node);

// ノード配列の全てのノードデータを出力する関数
void print_vector(std::vector<node> node_vector);

// 既存のノードかどうか判定する関数（返り値は一致したindex or
// 一致しない場合は-1）
int node_check(int a, std::vector<node> node_vector);

// 既存の隣接ノードかどうか判定する関数（返り値は一致した場合はindex or
// 一致しない場合は-1）
int neighbor_check(int a, struct node node);

// score配列とaccum配列を出力する関数
void print_score(std::vector<node> node_vector, double score[], double accum[]);

// edge行列を生成
void generate_edge(std::vector<node> node_vector, double *edge);

// edge行列を出力する関数
void print_edge(std::vector<node> node_vector, double *edge);

// score[] * edge[][] = accum[]を実行する関数
void Simplified_PageRank(double score[], double *edge, double accum[],
                         int size);
// accumのデータをscoreに代入してaccumを初期化(全要素0に)する関数
void accum_score(double accum[], double score[], int size);

// scoreとaccumの差分判定を行う関数
bool diff(double score[], double accum[], int size);