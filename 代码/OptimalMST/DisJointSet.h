#ifndef DISJOINTSET
#define DISJOINTSET

#include <iostream>
#include <vector>
using namespace std;

class DisJointSet{
    vector<int> fatherNode; /*��¼�����ÿ����ĸ��ڵ�*/
    vector<bool> choseEdge; /*��¼�ò����Ӧ��ͼ����Щ���Ѿ���ѡ����*/
    int graphN,graphM;
    class UGraph *inGraph;
public:
    void DisJointSetInit(int n, int m, UGraph *G = NULL);

    int FindRoot(int u);

    int SetFather(int father, int child);

    void UpdateDJS();

    void SetChoseEdge(int edgeID, bool value);

    vector<bool>& GetChoseEdgeArray();

};

#endif // DISJOINTSET
