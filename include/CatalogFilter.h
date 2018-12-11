#include <iostream>
#include <string>
#include <vector>

struct neighbor {
    int nid;
    double weight;
};

struct node {
    int id;
    vector<neighbor> negbr;
};
