#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
using namespace std;

#define N 8
#define M 20
#define MAXVALUE 3
bool visit[N+1][N+1];

int main(){
    freopen("in.txt","w",stdout);
    const int cas = 10;
    srand(time(0));
    for(int cc = 1; cc <= cas; ++cc){
        int n = rand() % N + 2;
        int m = rand() % min(n*(n-1)/2,M) + 1;
        memset(visit,false,sizeof(visit));
        printf("%d %d\n",n,m);
        for(int i = 1; i <= m; i++){
            while(true){
                int u = rand() % n + 1;
                int v = rand() % n + 1;
                if(visit[u][v] || u == v) continue;
                visit[u][v] = visit[v][u] = true;
                double existPro = (rand() % 5 + 6)*1.0 / 10;
                int value = rand() % MAXVALUE + 1;
                printf("%d %d %.6f %d\n",u, v, existPro, value);
                break;
            }
        }
    }

    return 0;
}
