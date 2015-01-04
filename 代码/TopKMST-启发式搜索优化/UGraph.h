#ifndef UGRAPH
#define UGRAPH

#include <iostream>
#include <vector>
#include "EdgeInfo.h"
#include "DisJointSet.h"
using namespace std;


typedef bool (*compareFunction) (const EdgeInfo &a, const EdgeInfo &b);

class UGraph{
    vector<EdgeInfo> edgeInfo;
    vector<int> bOutEdge;
    int graphN, graphM;
    int count;
    int MSTValue;
    double MSTProb;
    double lastProb;
    bool isSortEdge; /* «∑Ò“—æ≠≈≈–Ú*/
    bool storeMSTValue;
public:
    void GraphInit(int n, int m);

    void AddEdge(int u, int v, double existPro, int value);

    void SortEdge(compareFunction cmpFunc);

    int GetVertexNum();

    int GetEdgeNum();

    EdgeInfo* GetEdgeInfo(int edgeID);

    vector<int>* GetOptimalMST();

    int GetMSTValue();

    double GetMSTProb();

    double GetLastProb();

    vector<int>* GetLimitedMST(vector<int>* mstEdge, int mustEdgeNum, vector<int> *iOutEdge);
};

#endif

