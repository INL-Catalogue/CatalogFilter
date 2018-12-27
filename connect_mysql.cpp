#include <iostream>
#include "mysql_config.hpp"

using namespace std;
using namespace catalog;

int main() {
  DBClient *db;
  db            = new DBClient();
  string dbHost = "127.0.0.1";
  string dbUser = "root";
  string dbps   = "root";
  string dbName = "sample";
  if (db->connectDb((char *)&dbHost[0], (char *)&dbUser[0], (char *)&dbps[0],
                    (char *)&dbName[0]) < 0) {
    cerr << "DB CONNECT ERROR" << endl;
    return -1;
  } else {
    cout << "Connect DB" << endl;
  }
  int    nRow;
  string sql1 =
      "CREATE TABLE IF NOT EXISTS score (id int NOT NULL, score double, "
      "primary key(id));";
  if ((nRow = db->sendQuery((char *)sql1.c_str())) < 0) {
    cerr << "DB QUERY ERROR" << endl;
    return -1;
  }
  int    id    = 1;
  double score = 100.0;
  string sql2  = "insert into score (id, score) VALUES ";
  sql2 += "(";
  sql2 += IntToString(id) + ", ";
  sql2 += to_string(score);
  sql2 += ");";

  cout << "a" << endl;
  if ((nRow = db->sendQuery((char *)sql2.c_str())) < 0) {
    cerr << "DB QUERY ERROR" << endl;
    return -1;
  }
}