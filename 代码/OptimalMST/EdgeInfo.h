#ifndef EDGEINFO
#define EDGEINFO

class EdgeInfo{
public:
    int u,v;
    double existPro;
    int value;

    EdgeInfo(int u = 0, int v = 0, double existPro = 0.0, int value = 0){
        this->u = u;
        this->v = v;
        this->existPro = existPro;
        this->value = value;
    }
};

#endif // EDGEINFO
