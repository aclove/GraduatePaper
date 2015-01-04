#ifndef DISJOINTSET
#define DISJOINTSET

#include <iostream>
#include <vector>
#include "UGraph.h"
using namespace std;

class DisjointSet{
    vector<int> fatherNode;
    UGraph &graph;
public:
    DisjointSet(UGraph &G);
    int FindRoot(int v);
    void SetFather(int father, int child);
};

#endif // DISJOINTSET
