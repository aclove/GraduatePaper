#ifndef DISJOINTSET
#define DISJOINTSET

#include <iostream>
#include <vector>
using namespace std;

class DisJointSet{
    vector<int> fatherNode; /*记录并差集中每个点的父节点*/
    vector<bool> choseEdge; /*记录该并差集对应的图中哪些边已经被选择了*/
    int graphN,graphM;
    class UGraph *inGraph;
public:
    void DisJointSetInit(int n, int m, UGraph *G = NULL);

    int FindRoot(int u);

    int SetFather(int father, int child);

    void UpdateDJS();

    void SetChoseEdge(int edgeID, bool value);

    vector<bool>& GetChoseEdgeArray();

};

#endif // DISJOINTSET
