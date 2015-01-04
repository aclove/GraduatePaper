#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>
#include "UGraph.h"

using namespace std;

#define InRange(value, left, right) (value >= left && value <= right)

UGraph graph;

bool AllEdgeCmp(const EdgeInfo &a, const EdgeInfo &b){
    if(a.value != b.value){
        return a.value < b.value;
    }
    else{
        return a.existPro > b.existPro;
    }
}

void SearchMST(vector<int> &mustEdge, vector<bool> &outEdge){
    int preMustNum = mustEdge.size();
    vector<int> newMST = graph.GetLimitedMST(mustEdge, outEdge);
    //print newMST
    if(newMST.size() == 0) return;
    for(int i = mustEdge.size(); i < newMST.size(); ++i){
        outEdge[newMST[i]] = true;
        SearchMST(mustEdge, outEdge);
        mustEdge.push_back(newMST[i]);
        outEdge[newMST[i]] = false;
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
    freopen("out1.txt","w",stdout);

    printf("%10s %10s %10s\n","n", "m", "RunTime");
    clock_t totalT;

    while(InitAndInput()){
        clock_t start = clock();
        vector<int> mustEdge(0);
        vector<bool> outEdge(graph.GetEdgeNum()+1,0);
        vector<int> OptimalMST = graph.GetOptimalMST();
        if(OptimalMST.size() + 1 == graph.GetVertexNum()){
            SearchMST(mustEdge, outEdge);
        }
        clock_t end = clock();
        totalT = (end-start);
        printf("%10d %10d %10f\n", graph.GetVertexNum(), graph.GetEdgeNum(), totalT*1.0/CLOCKS_PER_SEC);
    }
    return 0;
}
