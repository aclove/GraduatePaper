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

vector<int> UGraph::GetOptimalMST(){
    vector<int> edgeSet;
    DisJointSet tmpDJS;
    tmpDJS.DisJointSetInit(graphN, graphM, this);
    for(int i = 0; i < graphM; i++){
        int ru = tmpDJS.FindRoot(edgeInfo[i].u);
        int rv = tmpDJS.FindRoot(edgeInfo[i].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        MSTValue += edgeInfo[i].value;
        edgeSet.push_back(i);
    }
    return edgeSet;
}

int UGraph::GetMSTValue(){
    return MSTValue;
}

/*mustEdge[i]为真则表示第i条边必须要选， inEdge[i]为假表示第i条边必须不能选*/
vector<int> UGraph::GetLimitedMST(vector<int> &inEdge, vector<bool> &outEdge){
    vector<int> edgeSet(inEdge);
    DisJointSet tmpDJS;
    tmpDJS.DisJointSetInit(graphN, graphM, this);
    int tmpValue = 0;
    for(int i = 0; i < inEdge.size(); i++){
        int j = inEdge[i];
        int ru = tmpDJS.FindRoot(edgeInfo[j].u);
        int rv = tmpDJS.FindRoot(edgeInfo[j].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        tmpValue += edgeInfo[j].value;
    }
    for(int i = 0; i < graphM; i++){
        if(outEdge[i]) continue;
        int ru = tmpDJS.FindRoot(edgeInfo[i].u);
        int rv = tmpDJS.FindRoot(edgeInfo[i].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        edgeSet.push_back(i);
        tmpValue += edgeInfo[i].value;
    }
    if(tmpValue == MSTValue) return edgeSet;
    else return vector<int>(0);
}


