#ifndef HEADER_H
#define HEADER_H
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include<iostream>
#include<cstdarg>
#include<math.h>
#include<vector>
using namespace std;

const Uint32 COLOR_WHITE = 4294967295;
struct wcCoord{
    float x;
    float y;
    float z;
    wcCoord(){
    }
    wcCoord(float ax, float ay, float az){
        x=ax;y=ay;z=az;
    }
    inline bool operator == (wcCoord a){
        return (x==a.x && y==a.y && z==a.z);
    }
    void toString(){
        cout<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
    }
};
struct wcPoint{
    float x;
    float y;
    float z;
    inline float getDeterminant(){
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }
    inline void reduceToUnit(){
        float det = getDeterminant();
        if (det == 0){
            cout<<"Error!! Determinant equals zero (ViewPort Matrix)"<<endl;
            return;
        }
        x = x / det;
        y = y / det;
        z = z / det;
    }
    inline wcPoint operator * (wcPoint a){
        return wcPoint { y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x};
    }
    inline void toString(){
        cout<<x<<" "<<y<<" "<<z<<endl;
    }
};
struct Edge{
    unsigned int iCoord, fCoord;
    Edge(){
    }
    Edge(int a, int b){
        iCoord = a;
        fCoord = b;
    }
    inline bool operator == (Edge a){
        return (iCoord == a.iCoord && fCoord == a.fCoord);
    }
};
struct Polygon{
    vector<Edge*> polyEdges;
    Edge *first, *second, *third;
    Polygon(Edge* a, Edge* b, Edge* c){
        first = a;
        second = b;
        third = c;
    }
    Polygon(int numArg, ...){
        va_list args;
        va_start(args, numArg);
        for (int i = 0 ; i < numArg ; i++){
            polyEdges.push_back(va_arg(args, Edge*));
        }
        va_end(args);
    }
};

#endif
