#ifndef UGRAPH
#define UGRAPH

#include <iostream>
#include <vector>
#include "EdgeInfo.h"
using namespace std;


typedef bool (*compareFunction) (const EdgeInfo &a, const EdgeInfo &b);

class UGraph{
    vector<EdgeInfo> edgeInfo;
    int graphN, graphM;
    int MSTValue;
    bool isSortEdge; /* «∑Ò“—æ≠≈≈–Ú*/
    bool storeMSTValue;
public:
    void GraphInit(int n, int m);

    void AddEdge(int u, int v, double existPro, int value);

    void SortEdge(compareFunction cmpFunc);

    int GetVertexNum();

    int GetEdgeNum();

    EdgeInfo* GetEdgeInfo(int edgeID);

    vector<int> GetOptimalMST();

    int GetMSTValue();

    vector<int> GetLimitedMST(vector<int> &inEdge, vector<bool> &outEdge);
};

#endif

