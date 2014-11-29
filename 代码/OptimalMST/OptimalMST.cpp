#include <iostream>
#include <cstdio>
#include <cmath>
#include "UGraph.h"
#include "DisJointSet.h"
using namespace std;

#define N 101
#define M 10001

UGraph graph;

int head[N];

bool AllEdgeCmp(const EdgeInfo &a, const EdgeInfo &b){
    if(a.value != b.value){
        return a.value < b.value;
    }
    else{
        return a.existPro > b.existPro;
    }
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

double SolveMethod(){
    double optimalValue = 0;
    DisJointSet DJS;
    DJS.DisJointSetInit(graph.GetVertexNum(), graph.GetEdgeNum(), &graph);
    for(int edgeID = 0; edgeID < graph.GetEdgeNum(); ++edgeID){
        EdgeInfo* pNewEdgeInfo = graph.GetEdgeInfo(edgeID);
        int nodeU = pNewEdgeInfo->u;
        int nodeV = pNewEdgeInfo->v;
        int rootU = DJS.FindRoot(nodeU);
        int rootV = DJS.FindRoot(nodeV);
        if(rootU != rootV){
            DJS.SetFather(rootU, rootV);
            optimalValue += log(pNewEdgeInfo->existPro);
        }
    }
    return exp(optimalValue);
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    while(InitAndInput()){
        if(graph.GetMSTValue() == -1){
            printf("MST of the main subgraph not exist!\n");
            continue;
        }
        else printf("MSTValue of the main subgraph is %d\n",graph.GetMSTValue());
        printf("The probability of the OptimalMST is %f\n",SolveMethod());
    }
    return 0;
}
