#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>
#include <queue>
#include "UGraph.h"

using namespace std;

#define InRange(value, left, right) (value >= left && value <= right)

struct Elems{
    vector<int> *outEdge;
    vector<int> *mstEdge;
    int mustEdgeNum;
    double prior;
};

UGraph graph;
vector<int> arrTopK;

bool AllEdgeCmp(const EdgeInfo &a, const EdgeInfo &b){
    if(a.value != b.value){
        return a.value < b.value;
    }
    else{
        return a.existPro > b.existPro;
    }
}

struct MstCmp{
    bool operator()(const Elems* a, const Elems* b){
        return a->prior < b->prior;
    }
};

void TopKMST(int K){
    priority_queue<Elems*, vector<Elems*>, MstCmp> que;
    vector<int> *optimalMST = graph.GetOptimalMST();
    if(optimalMST->size() + 1 != graph.GetVertexNum()) return;
    Elems *newElem = new Elems();
    Elems *nxtElem;
    newElem->outEdge = new vector<int>(0);
    newElem->mstEdge = optimalMST;
    newElem->mustEdgeNum = 0;
    newElem->prior = graph.GetMSTProb();
    que.push(newElem);
    //cerr << K << endl;
    while(!que.empty()){
        newElem = que.top();
        que.pop();
//        cerr << newElem->prior << endl;
        if(--K > 0){
            for(int i = newElem->mustEdgeNum; i < newElem->mstEdge->size(); ++i){
                nxtElem = new Elems();
                nxtElem->outEdge = new vector<int>(newElem->outEdge->begin(), newElem->outEdge->end());
                nxtElem->outEdge->push_back(newElem->mstEdge->at(i));
                nxtElem->mustEdgeNum = i;
                nxtElem->mstEdge = graph.GetLimitedMST(newElem->mstEdge, i, nxtElem->outEdge);
                nxtElem->prior = graph.GetLastProb();
                if(nxtElem->mstEdge->size() != 0){
                    que.push(nxtElem);
                }
                else{
                    delete nxtElem->mstEdge;
                    delete nxtElem->outEdge;
                    delete nxtElem;
                }
            }
        }
        delete newElem->mstEdge;
        delete newElem->outEdge;
        delete newElem;
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

void GenerateTopKValue(){
    arrTopK.push_back(1);
    int addValue = 1;
    for(int i = 1; i < 100; ++i){
        arrTopK.push_back(arrTopK[i-1] + addValue);
        if(i % 9 == 0) addValue *= 10;
    }
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    printf("%10s %10s\n","K", "RunTime");
    clock_t totalT;
    GenerateTopKValue();

    while(InitAndInput()){
        for(int i = 1; i < 60; ++i){
            clock_t start = clock();
            TopKMST(i*10000);
            clock_t end = clock();
            totalT = (end-start);
            printf("%10d %10f\n", i*10000, totalT*1.0/CLOCKS_PER_SEC);
        }
    }
    return 0;
}
