#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>
#include "UGraph.h"
#include "MST.h"
#include "EdgeInfo.h"
#include "DisJointSet.h"

using namespace std;
#define InRange(value, left, right) (value >= left && value <= right)


typedef bool (*compareFunction) (const EdgeInfo &a, const EdgeInfo &b);
bool AllEdgeCmp(const EdgeInfo &a, const EdgeInfo &b){
    if(a.value != b.value){
        return a.value < b.value;
    }
    else return a.existPro > b.existPro;
}

double stableMST;
int Nnumber;
UGraph graph;

void Substitute(vector<bool> &outEdge, CMST &curMST, vector<int> &replace){
    vector<int>& searchOrder = curMST.GetSearchOrder();
    vector<pair<int, int> >& childRange = curMST.GetChildRange();
    vector<pair<int,int> >& father = curMST.GetFather();
    int m = graph.GetEdgeNum();
    DisjointSet tmpDJS(graph);

    for(int i = 0; i < m; i++){

        if(outEdge[i]) continue;
        EdgeInfo &edgeInfo = graph.GetEdgeInfo(i);
        int u = edgeInfo.u;
        int v = edgeInfo.v;
        if(father[u].first == v || father[v].first == u) continue;
        int value = edgeInfo.value;
        int ru,rv,tu,tv;
        tu = ru = tmpDJS.FindRoot(u);
        tv = rv = tmpDJS.FindRoot(v);
        int srv = searchOrder[rv];
        int sru = searchOrder[ru];

        while(srv < childRange[tu].first || srv > childRange[tu].second){
            tmpDJS.SetFather(ru, tu);
            int newValue = graph.GetEdgeInfo(father[tu].second).value;
            if(value == newValue) replace[father[tu].second] = i;
            tu = tmpDJS.FindRoot(father[tu].first);
        }
        while(sru < childRange[tv].first || sru > childRange[tv].second){
            tmpDJS.SetFather(ru, tv);
            int newValue = graph.GetEdgeInfo(father[tv].second).value;
            if(value == newValue) replace[father[tv].second] = i;
            tv = tmpDJS.FindRoot(father[tv].first);
        }
        tmpDJS.SetFather(tu, ru);
    }
}


void SearchMST(vector<int> &mustEdge, vector<bool> &outEdge, CMST &curMST){
    vector<int> replace(graph.GetEdgeNum(),-1);
    vector<int>& includedEdge = curMST.GetIncludedEdge();
    int preMustNum = mustEdge.size();
    Substitute(outEdge, curMST, replace);
    ++Nnumber;
    for(int i = preMustNum; i < includedEdge.size(); i++){
        int tmpEdge = includedEdge[i];
        if(replace[tmpEdge] == -1){
            mustEdge.push_back(tmpEdge);
            continue;
        }

        includedEdge[i] = replace[tmpEdge];
        outEdge[tmpEdge] = true;

        curMST.DeleteEdge(tmpEdge);
        curMST.AddEdge(replace[tmpEdge]);

        curMST.MSTNodeSort(graph.GetVertexNum(),-1,-1,1);

        SearchMST(mustEdge, outEdge, curMST);

        curMST.AddEdge(tmpEdge);
        curMST.DeleteEdge(replace[tmpEdge]);
        outEdge[tmpEdge] = false;
        mustEdge.push_back(tmpEdge);
        includedEdge[i] = tmpEdge;
    }
    mustEdge.resize(preMustNum);
}


/*读入不确定图并对图进行初始化*/
bool InitAndInput(){
    int n,m;
    if(scanf("%d%d",&n,&m) != 2) return false;
    graph.GraphInit(n,m);
    for(int i = 0; i < m; i++){
        int a,b,d;
        double c;
        scanf("%d%d%lf%d",&a, &b, &c, &d);
        graph.AddEdge(a,b,c,d);
    }
    graph.SortEdge(AllEdgeCmp);
    return true;
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    printf("%10s %10s\n","N", "RunTime");
    clock_t totalT = 0;
    while(InitAndInput()){
        Nnumber = 0;
        clock_t start = clock();
        vector<int> mustEdge(0);
        vector<bool> outEdge(graph.GetEdgeNum(),0);
        vector<int> arbitraryMST = graph.GetArbitraryMST();
        if(arbitraryMST.size() + 1 == graph.GetVertexNum()){
            CMST startMST(graph, arbitraryMST);
            startMST.MSTSetting();
            SearchMST(mustEdge, outEdge, startMST);
        }
        clock_t end = clock();
        totalT = (end-start);
        printf("%10d %10f\n",Nnumber, totalT*1.0/CLOCKS_PER_SEC);
    }
    return 0;
}
