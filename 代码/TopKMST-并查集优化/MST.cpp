#include "MST.h"
#include "EdgeInfo.h"

CMST::CMST(UGraph &G, vector<int> edgeSet) : graph(G){
    includedEdge = edgeSet;
    BuildMSTGraph();
}

void CMST::BuildMSTGraph(){
    MSTEdge.assign(graph.GetVertexNum()+1, vector<int>(0));
    edgePos.resize(graph.GetEdgeNum(), make_pair(-1,-1));
    for(int i = 0; i < includedEdge.size(); i++){
        EdgeInfo &edgeInfo = graph.GetEdgeInfo(includedEdge[i]);
        MSTEdge[edgeInfo.u].push_back(includedEdge[i]);
        MSTEdge[edgeInfo.v].push_back(includedEdge[i]);
        edgePos[includedEdge[i]] = make_pair(MSTEdge[edgeInfo.u].size()-1,MSTEdge[edgeInfo.v].size()-1);
    }
}

void CMST::MSTSetting(){
    int graphN = graph.GetVertexNum();
    searchOrder.resize(graphN+1);
    childRange.resize(graphN+1);
    father.resize(graphN+1);
    MSTNodeSort(graphN, -1, -1, 1);
}

int CMST::MSTNodeSort(int u, int f, int edgeID, int newID){
    searchOrder[u] = newID;
    father[u].first = f;
    father[u].second = edgeID;
    int tmpID = newID;
    for(int i = 0; i < MSTEdge[u].size(); i++){
        EdgeInfo &edgeInfo = graph.GetEdgeInfo(MSTEdge[u][i]);
        int v = (edgeInfo.u == u ? edgeInfo.v : edgeInfo.u);
        if(v != f) tmpID = MSTNodeSort(v, u, MSTEdge[u][i], tmpID+1);
    }
    childRange[u] = make_pair(newID, tmpID);
    return tmpID;
}

vector<int>& CMST::GetIncludedEdge(){
    return includedEdge;
}

vector<int>& CMST::GetSearchOrder(){
    return searchOrder;
}

vector<pair<int,int> >& CMST::GetChildRange(){
    return childRange;
}

vector<pair<int,int> >& CMST::GetFather(){
    return father;
}

void CMST::AddEdge(int edgeID){
    EdgeInfo &edgeInfo = graph.GetEdgeInfo(edgeID);
    int u = edgeInfo.u;
    int v = edgeInfo.v;
    MSTEdge[u].push_back(edgeID);
    MSTEdge[v].push_back(edgeID);
    edgePos[edgeID] = make_pair(MSTEdge[u].size()-1,MSTEdge[v].size()-1);
}

void CMST::DeleteEdge(int edgeID){
    EdgeInfo &edgeInfo = graph.GetEdgeInfo(edgeID);
    int u = edgeInfo.u;
    int v = edgeInfo.v;

    int sz = MSTEdge[u].size();
    int pos = edgePos[edgeID].first;
    int rEdge = MSTEdge[u][sz-1];
    MSTEdge[u][pos] = rEdge;
    MSTEdge[u].pop_back();
    if(graph.GetEdgeInfo(rEdge).u == u) edgePos[rEdge].first = pos;
    else edgePos[rEdge].second = pos;

    sz = MSTEdge[v].size();
    pos = edgePos[edgeID].second;
    rEdge = MSTEdge[v][sz-1];
    MSTEdge[v][pos] = rEdge;
    MSTEdge[v].pop_back();
    if(graph.GetEdgeInfo(rEdge).u == v) edgePos[rEdge].first = pos;
    else edgePos[rEdge].second = pos;

    edgePos[edgeID] = make_pair(-1,-1);

}
