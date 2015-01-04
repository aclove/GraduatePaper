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
    count = 0;
    edgeInfo.resize(0);
    bOutEdge.assign(m,0);
    isSortEdge = false;
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

vector<int>* UGraph::GetOptimalMST(){
    vector<int> *edgeSet = new vector<int>(0);
    DisJointSet tmpDJS;
    tmpDJS.DisJointSetInit(graphN, graphM, this);
    MSTValue = 0;
    MSTProb = 1.0;
    for(int i = 0; i < graphM; i++){
        int ru = tmpDJS.FindRoot(edgeInfo[i].u);
        int rv = tmpDJS.FindRoot(edgeInfo[i].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        MSTValue += edgeInfo[i].value;
        MSTProb *= edgeInfo[i].existPro;
        edgeSet->push_back(i);
    }
    return edgeSet;
}

int UGraph::GetMSTValue(){
    return MSTValue;
}

double UGraph::GetMSTProb(){
    return MSTProb;
}

double UGraph::GetLastProb(){
    return lastProb;
}

vector<int>* UGraph::GetLimitedMST(vector<int>* mstEdge, int mustEdgeNum, vector<int> *iOutEdge){
    vector<int>* edgeSet = new vector<int>(mstEdge->begin(), mstEdge->begin() + mustEdgeNum);
    DisJointSet tmpDJS;
    tmpDJS.DisJointSetInit(graphN, graphM, this);
    int tmpValue = 0;
    lastProb = 1.0;
    ++count;
    //cerr << mstEdge->size() << " " << mustEdgeNum << " " << iOutEdge->size() << endl;
    //cerr << "iOutEdge:" << iOutEdge->at(0) << endl;
    for(int i = 0; i < iOutEdge->size(); ++i){
        bOutEdge[iOutEdge->at(i)] = count;
    }
    for(int i = 0; i < mustEdgeNum; i++){
        int j = mstEdge->at(i);
        int ru = tmpDJS.FindRoot(edgeInfo[j].u);
        int rv = tmpDJS.FindRoot(edgeInfo[j].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        tmpValue += edgeInfo[j].value;
        lastProb *= edgeInfo[j].existPro;
    }
    for(int i = 0; i < graphM; i++){
        if(bOutEdge[i] == count) continue;
        int ru = tmpDJS.FindRoot(edgeInfo[i].u);
        int rv = tmpDJS.FindRoot(edgeInfo[i].v);
        if(ru == rv) continue;
        tmpDJS.SetFather(ru, rv);
        edgeSet->push_back(i);
        tmpValue += edgeInfo[i].value;
        lastProb *= edgeInfo[i].existPro;
    }
    if(tmpValue != MSTValue) edgeSet->clear();
    return edgeSet;
}


