#include "DisJointSet.h"
#include "EdgeInfo.h"
#include "UGraph.h"

DisjointSet::DisjointSet(UGraph &G) : graph(G){
    int graphN = graph.GetVertexNum();
    fatherNode.resize(graphN+1);
    for(int i = 1; i <= graphN; i++) fatherNode[i] = i;
}

int DisjointSet::FindRoot(int v){
    if(fatherNode[v] == v) return v;
    fatherNode[v] = FindRoot(fatherNode[v]);
    return fatherNode[v];
}

void DisjointSet::SetFather(int father, int child){
    fatherNode[child] = father;
}
