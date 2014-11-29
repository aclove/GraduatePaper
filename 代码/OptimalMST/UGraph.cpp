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
    isSortEdge = false;
    storeMSTValue = false;
}

void UGraph::AddEdge(int u, int v, double existPro, int value){
    edgeInfo.push_back(EdgeInfo(u,v,existPro,value));
}

void UGraph::SortEdge(compareFunction cmpFunc){
    assert(edgeInfo.size() == graphM);
    sort(edgeInfo.begin(),edgeInfo.end(),cmpFunc);
    isSortEdge = true;
}

int UGraph::GetVertexNum(){
    return graphN;
}

int UGraph::GetEdgeNum(){
    return graphM;
}

EdgeInfo* UGraph::GetEdgeInfo(int edgeID){
    if(edgeID < 0 || edgeID >= graphM) return NULL;
    return &edgeInfo[edgeID];
}

int UGraph::GetMSTValue(){
    if(!storeMSTValue) MSTValue = GetLimitedMSTValue(nullArray, nullArray);
    storeMSTValue = true;
    return MSTValue;
}

/*mustEdge[i]为真则表示第i条边必须要选， inEdge[i]为假表示第i条边必须不能选*/
int UGraph::GetLimitedMSTValue(vector<bool> &mustEdge, vector<bool> &inEdge){/*使用kruskal算法求解最小生成树*/
    int MSTValue = 0;
    int edgeCount = 0;
    DisJointSet tmpDJS;
    tmpDJS.DisJointSetInit(graphN, graphM);
    assert(isSortEdge == true);
    for(int i = 0; i < mustEdge.size(); i++){
        if(!mustEdge[i]) continue;
        if(inEdge.size() > i){
            assert(!(mustEdge[i] && !inEdge[i]));
        }
        int ru = tmpDJS.FindRoot(edgeInfo[i].u);
        int rv = tmpDJS.FindRoot(edgeInfo[i].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        MSTValue += edgeInfo[i].value;
        ++edgeCount;
    }

    for(int i = 0; i < graphM; i++){
        if(mustEdge.size() > i && mustEdge[i]) continue;
        if(inEdge.size() > i && !inEdge[i]) continue;
        int ru = tmpDJS.FindRoot(edgeInfo[i].u);
        int rv = tmpDJS.FindRoot(edgeInfo[i].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        MSTValue += edgeInfo[i].value;
        ++edgeCount;
    }
    if(edgeCount < graphN-1) return -1;
    return MSTValue;
}


