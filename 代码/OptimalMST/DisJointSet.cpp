#include "DisJointSet.h"
#include "EdgeInfo.h"
#include "UGraph.h"

void DisJointSet::DisJointSetInit(int n, int m, UGraph *G){
    fatherNode.resize(n+1);
    choseEdge.resize(m);
    for(int i = 1; i <= n; i++) fatherNode[i] = i;
    fill(choseEdge.begin(),choseEdge.end(),0);
    graphN = n;
    graphM = m;
    inGraph = G;
}

int DisJointSet::FindRoot(int u){
    if(fatherNode[u] == u) return u;
    fatherNode[u] = FindRoot(fatherNode[u]);
    return fatherNode[u];
}

int DisJointSet::SetFather(int father, int child){
    fatherNode[child] = father;
}

void DisJointSet::UpdateDJS(){
    for(int i = 1; i <= graphN; i++) fatherNode[i] = i;
    for(int i = 0; i < choseEdge.size(); i++){
        if(!choseEdge[i]) continue;
        EdgeInfo *edgeInfo = inGraph->GetEdgeInfo(i);
        int ru = FindRoot(edgeInfo->u);
        int rv = FindRoot(edgeInfo->v);
        if(ru == rv) continue;
        SetFather(ru, rv);
    }
}

void DisJointSet::SetChoseEdge(int edgeID, bool value){
    choseEdge[edgeID] = value;
}

vector<bool>& DisJointSet::GetChoseEdgeArray(){
    return choseEdge;
}
