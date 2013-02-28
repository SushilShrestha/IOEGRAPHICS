#include"header.h"
class sandbox{
public:
    void test();
private:
//    struct Edge{
//        wcCoord *iCoord, *fCoord;
//        Edge(wcCoord* a, wcCoord* b){
//            iCoord = a;
//            fCoord = b;
//        }
//    };
//    struct Polygon{
//        vector<Edge*> polyEdges;
//        Edge *first, *second, *third;
//        Polygon(Edge* a, Edge* b, Edge* c){
//            first = a;
//            second = b;
//            third = c;
//        }
//    };
    struct tempStruct{
        int x,y;
    };

    vector<wcCoord> vertexTable;
    vector<Edge> edgetable;
    vector<Polygon> polygonTable;

    vector<wcCoord>::iterator vertexIter;
};
#include <cstdarg>
void someFunction(int numArg, ...){
    cout<<"you are inside some function"<<endl;

    cout <<"now printing the variable arguments"<<endl;
    va_list args;
    va_start(args, numArg);
    for (int i = 0 ; i < numArg ; i++)
        cout<<va_arg(args, wcCoord*)<<endl;
    va_end(args);

    cout<<"out of function"<<endl;
}

void sandbox::test(){
    wcCoord temp;

    int vSlice = 10 ;
    int hSlice = 10 ;
    int radius = 50 ;

    float dPhi = 360 / vSlice;
    float dTheta = 180 / hSlice;

    for (int j = 0 ; j < hSlice ; j++ ){
        for (int i = 0 ; i < vSlice ; i++){
            temp.x = radius * cos(dPhi * i * 3.1415 / 180) * cos(dTheta * j * 3.1415 / 180);
            temp.y = radius * sin(dPhi * i * 3.1415 / 180) * cos(dTheta * j * 3.1415 / 180);
            temp.z = radius * sin(dTheta * j * 3.1415 / 180);
            vertexTable.push_back(temp);
        }
    }
//    int n = vertexTable.size();
//    for (int i = 0 ; i <n ; i++){
//        cout<<vertexTable[i].x<<vertexTable[i].y<<vertexTable[i].z<<endl;
//    }

//
//    vertexTable.push_back(wcCoord(99,0,0));
//    vertexTable.push_back(wcCoord(0,10,0));
//    vertexTable.push_back(wcCoord(10,0,0));
//    vertexTable.push_back(wcCoord(10,10,0));
//    tempStruct t = {3,4};
//    edgetable.push_back(Edge(&vertexTable[0],&vertexTable[1]));
//    edgetable.push_back(Edge(&vertexTable[0],&vertexTable[2]));
//    edgetable.push_back(Edge(&vertexTable[0],&vertexTable[3]));
//    edgetable.push_back(Edge(&vertexTable[1],&vertexTable[2]));
//    edgetable.push_back(Edge(&vertexTable[1],&vertexTable[3]));
//    edgetable.push_back(Edge(&vertexTable[2],&vertexTable[3]));
//
//    wcCoord wx(99,0,0);
//    wcCoord wy(0,10,0);
//    cout<<(Edge(&vertexTable[0],&vertexTable[1]) == Edge(&wx, &wy))<<endl;
//
//    polygonTable.push_back(Polygon(&edgetable[0], &edgetable[1], &edgetable[2]));
//    polygonTable.push_back(Polygon(&edgetable[1], &edgetable[2], &edgetable[3]));
//    polygonTable.push_back(Polygon(&edgetable[2], &edgetable[3], &edgetable[4]));
//
//
////    cout<<&vertexTable[0]==&vertexTable[0]<<endl;
//
//    polygonTable.
//
//    float x = vertexTable[3].x;
////    cout<<vertexTable[0].toString()<<vertexTable[1].toString()<<vertexTable[2].toString()<<vertexTable[3].toString()<<endl;
//    cout <<"vertex table size "<< vertexTable.size()<<endl;
//    cout <<"edgge table size "<< edgetable.size()<<endl;
//    x = edgetable[0].iCoord->x;
//    cout<<"check "<<x<<endl;
//
//    double a = 4, b =5, c =6, d =7;
//    someFunction(2,&wx, &wy);
}


