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
