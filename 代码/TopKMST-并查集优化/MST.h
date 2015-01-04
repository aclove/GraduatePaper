#ifndef MST
#define MST

#include <vector>
#include <iostream>
#include "UGraph.h"
using namespace std;

class CMST{
    vector<int> includedEdge;
    vector<pair<int,int> > father;
    vector<int> searchOrder; /*遍历树后每个节点的从新编号*/
    vector<pair<int,int> > childRange;
    vector<vector<int> > MSTEdge;
    vector<pair<int, int> > edgePos;
    UGraph &graph;
public:
    CMST(UGraph &G, vector<int> edgeSet = vector<int>(0));

    void BuildMSTGraph();

    void MSTSetting();

    int MSTNodeSort(int u, int f, int edgeID, int newID);

    vector<int>& GetIncludedEdge();

    vector<int>& GetSearchOrder();

    vector<pair<int,int> >& GetChildRange();

    vector<pair<int,int> >& GetFather();

    void AddEdge(int edgeID);

    void DeleteEdge(int edgeID);

};

#endif
