#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "include/CatalogFilter.h"

using namespace std;
using namespace catalog;

int main() {
  //////////////////////////
  //  csvファイルの読み込み  //
  //////////////////////////

  clock_t start, end;
  double  exe_time = 0.0;
  start            = clock();

  std::ifstream ifs("data.csv");
  ifs.is_open();

  std::vector<node> node_vector;

  std::string line;
  while (std::getline(ifs, line)) {
    vector<int>         a;
    std::vector<string> strvec = split(line, ',');
    for (int i = 0; i < (int)strvec.size(); i++) {
      a.push_back(std::stoi(strvec.at(i)));
    }
    for (int i = 0; i < (int)a.size(); i++) {
      if ((int)node_vector.size() != 0) {
        // 2番目以降の要素の追加
        if (node_check(a.at(i), node_vector) == -1) {
          // 新出のノードの場合
          struct node n;
          n.id = a.at(i);
          struct neighbor ng;
          for (int j = 0; j < (int)a.size(); j++) {
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
          for (int k = 0; k < (int)a.size(); k++) {
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
      } else if ((int)node_vector.size() == 0) {
        // 1番最初の要素の追加
        struct node n;
        n.id = a.at(0);
        node_vector.push_back(n);
        for (int i = 1; i < (int)a.size(); i++) {
          struct neighbor ng;
          ng.id     = a.at(i);
          ng.weight = 1;
          node_vector.at(0).neighbor.push_back(ng);
        }
      }
    }
  }
  ifs.close();

  end            = clock();
  double io_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
  exe_time += io_time;
  start = clock();

  //////////////////////
  //  スコア配列の生成  //
  /////////////////////

  double score[(int)node_vector.size()];
  double accum[(int)node_vector.size()];

  for (int i = 0; i < (int)node_vector.size(); i++) {
    accum[i] = 0.0;
  }

  ///////////////////////////
  //  DBからデータを取り出す  //
  ///////////////////////////

  Data_get(node_vector, score);
  // print_score(node_vector, score, accum);
  end            = clock();
  double db_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
  exe_time += db_time;
  start = clock();

  /////////////////////
  //  edge行列の生成  //
  ////////////////////

  double **edge = new double *[(int)node_vector.size()];
  for (int i = 0; i < (int)node_vector.size(); i++)
    edge[i] = new double[(int)node_vector.size()];

  // double edge[(int)node_vector.size()][(int)node_vector.size()];
  for (int i = 0; i < (int)node_vector.size(); i++) {
    for (int j = 0; j < (int)node_vector.size(); j++) {
      edge[i][j] = 0;
    }
  }

  generate_edge(node_vector, edge);

  ///////////////////////////////////
  //  Simplified PageRank 計算処理  //
  ///////////////////////////////////

  int id;
  int index;

  end = clock();
  exe_time += (double)(end - start) / CLOCKS_PER_SEC * 1000;

  while (1) {
    cin >> id;
    if ((index = node_check(id, node_vector)) > 0)
      break;
    else
      cout << "Please input exist ID" << endl;
  }

  start = clock();

  double ac;
  ac           = score[index] * (-1);
  score[index] = ac;

  int count = 1;

  while (1) {
    // cout << "count " << count << endl;
    Simplified_PageRank(score, edge, accum, (int)node_vector.size());
    // accum[index] = ac;
    // print_score(node_vector, score, accum);
    if (diff(score, accum, (int)node_vector.size())) {
      accum_score(accum, score, (int)node_vector.size());
      break;
    }
    accum_score(accum, score, (int)node_vector.size());
    count++;
    // cout << endl;
  }
  cout << "count: " << count << endl;
  cout << "result" << endl;
  score[index] = ac;
  print_score(node_vector, score, accum);

  end = clock();
  exe_time += (double)(end - start) / CLOCKS_PER_SEC * 1000;

  cout << "I/O time: " << io_time << "(msec)" << endl;
  cout << "DB time: " << db_time << "(msec)" << endl;
  cout << "Comoute time: " << exe_time - io_time - db_time << "(ms)" << endl;
  cout << "Total time: " << exe_time << "(ms)" << endl;

  return 0;
}

std::vector<string> split(std::string &input, char delimiter) {
  std::istringstream  stream(input);
  std::string         field;
  std::vector<string> result;
  while (std::getline(stream, field, delimiter)) {
    result.push_back(field);
  }
  return result;
}

void print(struct node n) {
  std::cout << "id = " << n.id << endl;
  std::cout << "neighbor: ";
  for (int i = 0; i < (int)n.neighbor.size(); i++) {
    if (i == (int)n.neighbor.size() - 1)
      std::cout << n.neighbor.at(i).id << endl;
    else
      std::cout << n.neighbor.at(i).id << ", ";
  }
  std::cout << "weight:   ";
  for (int i = 0; i < (int)n.neighbor.size(); i++) {
    if (i == (int)n.neighbor.size() - 1)
      std::cout << n.neighbor.at(i).weight << endl;
    else
      std::cout << n.neighbor.at(i).weight << ", ";
  }
}

void print_vector(std::vector<node> node_vector) {
  for (int j = 0; j < (int)node_vector.size(); j++) {
    print(node_vector.at(j));
  }
}

int node_check(int a, std::vector<node> node_vector) {
  for (int i = 0; i < (int)node_vector.size(); i++) {
    if (a == node_vector.at(i).id) return i;
  }
  return -1;
}

int neighbor_check(int a, struct node n) {
  for (int i = 0; i < (int)n.neighbor.size(); i++) {
    if (a == n.neighbor.at(i).id) return i;
  }
  return -1;
}

void print_score(std::vector<node> node_vector, double score[],
                 double accum[]) {
  cout << "  id  |";
  for (int i = 0; i < (int)node_vector.size(); i++) {
    if (i == (int)node_vector.size() - 1)
      cout << "  " << node_vector.at(i).id << "  |" << endl;
    else
      cout << "  " << node_vector.at(i).id << "  |";
  }
  cout << "score |";
  for (int i = 0; i < (int)node_vector.size(); i++) {
    if (i == (int)node_vector.size() - 1)
      cout << " " << score[i] << " |" << endl;
    else
      cout << " " << score[i] << " |";
  }
  cout << "accum |";
  for (int i = 0; i < (int)node_vector.size(); i++) {
    if (i == (int)node_vector.size() - 1)
      cout << " " << accum[i] << " |" << endl;
    else
      cout << " " << accum[i] << " |";
  }
}

void generate_edge(std::vector<node> node_vector, double **edge) {
  for (int i = 0; i < (int)node_vector.size(); i++) {
    double element = 1.0 / (double)node_vector.at(i).neighbor.size();
    for (int j = 0; j < (int)node_vector.size(); j++) {
      int k = neighbor_check(node_vector.at(j).id, node_vector.at(i));
      if (k != -1) edge[i][j] = element;
      //*(edge + i * (int)node_vector.size() + j) = element;
    }
  }
}

void print_edge(std::vector<node> node_vector, double **edge) {
  for (int i = 0; i < (int)node_vector.size(); i++) {
    cout << "| " << node_vector.at(i).id << " |";
    for (int j = 0; j < (int)node_vector.size(); j++) {
      cout << " " << edge[i][j] << " ";
      // cout << " " << *(edge + i * (int)node_vector.size() + j) << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void Simplified_PageRank(double score[], double **edge, double accum[],
                         int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      double e = edge[j][i];
      // double e = *(edge + j * size + i);
      accum[i] = accum[i] + score[j] * e;
    }
  }
}

void accum_score(double accum[], double score[], int size) {
  for (int i = 0; i < size; i++) {
    score[i] = accum[i];
    accum[i] = 0;
  }
}

bool diff(double score[], double accum[], int size) {
  for (int i = 0; i < size; i++)
    if (std::fabs(accum[i] - score[i]) > 0.00001) return false;
  return true;
}

int Data_get(std::vector<node> node_vector, double score[]) {
  DBClient *db;
  db = new DBClient();

  if (db->connectDb((char *)&dbHost[0], (char *)&dbUser[0], (char *)&dbps[0],
                    (char *)&dbName[0]) < 0) {
    cerr << "DB CONNECT ERROR" << endl;
    return -1;
  } else {
    cout << "Connect DB" << endl;
  }

  int    nRow;
  string sql1 = "SELECT * FROM score;";
  if ((nRow = db->sendQuery((char *)sql1.c_str())) < 0) {
    cerr << "DB QUERY ERROR" << endl;
    return -1;
  }

  for (int i = 0; i < nRow; i++) {
    char **result = db->getResult();
    int    id     = atoi(result[0]);
    double score1 = atof(result[1]);
    int    index  = node_check(id, node_vector);
    score[index]  = score1;
  }

  return 0;
}