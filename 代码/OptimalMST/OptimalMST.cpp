#include <iostream>
#include <cstdio>
#include "UGraph.h"
using namespace std;

#define N 101
#define M 10001

UGraph graph;

int head[N];

bool AllEdgeCmp(const EdgeInfo &a, const EdgeInfo &b){
    return a.value < b.value;
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
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(InitAndInput()){
        if(graph.GetMSTValue() == -1){
            printf("MST of the main subgraph not exist!\n");
            continue;
        }
        else printf("MSTValue of the main subgraph is %d\n",graph.GetMSTValue());
        //SolveMethod();
        //printf("%f\n",stableMST);
    }
    return 0;
}
