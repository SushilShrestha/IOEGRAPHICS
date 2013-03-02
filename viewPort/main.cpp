#include "header.h"
#include "library.h"



int main ( int argc, char** argv ){
    freopen("CON","w",stdout);
//    wcPoint a(15,0,100);
//    wcPoint b(0,1,0);
//    wcPoint c = a*b;
    float rotAngle = 0;
//    graphicsLibrary engine(true);
graphicsLibrary engine;
    engine.setViewPoint(wcCoord(0, 0, 10), 200);
    engine.sandBox();
//    engine.drawWC(wcCoord(100,100,0),true);
////    engine.drawWC(wcCoord(100, 100, 50), true);
////    wcCoord initial(23,34,67);
////    wcCoord final(23,34,54);
////    engine.drawLine(COLOR_WHITE, initial, final);
//    engine.generateWC3D();
//    engine.rotatex(90);
    while (!engine.getDone()){
////        engine.drawWC(wcCoord(100,100,0));
////        engine.drawWC(wcCoord(100, 100, 50));
        engine.eventHandler();
//        engine.sandBox();

////        for (int i = 0; i<100; i++){
////            engine.drawPixel(4294967295, i, i);
//////            PutPixel16(screen, i, i, 4294967295);
////        }
//        engine.drawWC(wcCoord (0, 0, 0));
//        engine.drawWC(wcCoord (100, 0, 0));
//        engine.drawWC(wcCoord (0, 100, 0));
//        engine.drawWC(wcCoord (100, 100, 0));
//        engine.drawWC(wcCoord (0, 0, 100));
//        engine.drawWC(wcCoord (100, 0, 100));
//        engine.drawWC(wcCoord (0, 100, 100));
//        engine.drawWC(wcCoord (100, 100, 100));
//        engine.drawLine(COLOR_WHITE, wcCoord(0,0,0), wcCoord(100, 0, 0));
//        engine.drawLine(COLOR_WHITE, wcCoord(100, 0, 0), wcCoord(100,100,0));
//        engine.drawLine(COLOR_WHITE, wcCoord(100,100,0), wcCoord(0, 100, 0));
//        engine.drawLine(COLOR_WHITE, wcCoord(0,100,0), wcCoord(0, 0, 0));
//
//        engine.drawLine(COLOR_WHITE, wcCoord(0,0,100), wcCoord(100, 0, 100));
//        engine.drawLine(COLOR_WHITE, wcCoord(100, 0, 100), wcCoord(100,100,100));
//        engine.drawLine(COLOR_WHITE, wcCoord(100,100,100), wcCoord(0, 100, 100));
//        engine.drawLine(COLOR_WHITE, wcCoord(0,100, 100), wcCoord(0, 0, 100));
//
//        engine.drawLine(COLOR_WHITE, wcCoord(100,0,0), wcCoord(100, 0, 100));
//        engine.drawLine(COLOR_WHITE, wcCoord(100, 100, 0), wcCoord(100,100,100));
//        engine.drawLine(COLOR_WHITE, wcCoord(0,100,0), wcCoord(0, 100, 100));
//        engine.drawLine(COLOR_WHITE, wcCoord(0,0, 0), wcCoord(0, 0, 100));
//
        engine.rotatey(rotAngle);
        engine.renderWiredFrame();
//        engine.scanLine();
        engine.sandBox();
        rotAngle += (rotAngle>360)?-360:5;
//////        engine.drawLine(COLOR_WHITE, wcCoord(100,100,0), wcCoord(100,100,100));
//        engine.generateWC3D();
        engine.flipScreen();
    } // end main loop
    return 0;
}

void drawCube(){

}
