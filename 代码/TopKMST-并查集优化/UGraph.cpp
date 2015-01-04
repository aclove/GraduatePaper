#include <cassert>
#include <vector>
#include <algorithm>
#include "UGraph.h"
#include "DisJointSet.h"
using namespace std;

vector<bool> nullArray(0);
void UGraph::GraphInit(int n, int m){
    graphN = n;
    graphM = m;
    edgeInfo.resize(0);
    MSTValue = 0;
    MSTPossible = 1.0;
}

void UGraph::AddEdge(int u, int v, double existPro, int value){
    edgeInfo.push_back(EdgeInfo(u,v,existPro,value));
}

void UGraph::SortEdge(compareFunction cmpFunc){
    assert(edgeInfo.size() == graphM);
    sort(edgeInfo.begin(),edgeInfo.end(),cmpFunc);
}

int UGraph::GetVertexNum(){
    return graphN;
}

int UGraph::GetEdgeNum(){
    return graphM;
}


EdgeInfo& UGraph::GetEdgeInfo(int edgeID){
    return edgeInfo[edgeID];
}

int UGraph::GetMSTValue(){
    return MSTValue;
}

double UGraph::GetMSTPossible(){
    return MSTPossible;
}

vector<int> UGraph::GetArbitraryMST(){
    vector<int> edgeSet;
    DisjointSet tmpDJS(*this);
    for(int i = 0; i < graphM; i++){
        int ru = tmpDJS.FindRoot(edgeInfo[i].u);
        int rv = tmpDJS.FindRoot(edgeInfo[i].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        MSTValue += edgeInfo[i].value;
        MSTPossible *= edgeInfo[i].existPro;
        edgeSet.push_back(i);
    }
    return edgeSet;
}



