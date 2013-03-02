#include "header.h"

class graphicsLibrary{
    public:
        graphicsLibrary();
        graphicsLibrary(bool test){}
        ~graphicsLibrary();

        bool initializeSDL();
        bool loadScreen();
        void loadInitialTransMat();
        void cleanUpMesh();

        void setViewPoint(wcCoord, int);
        void updateViewPointMat();

        void updateProjectionMat();

        void rotatex(float angle);
        void rotatey(float angle);
        void rotatez(float angle);

        void drawPixel(/*SDL_Surface*,*/ Uint32, int, int);
        void drawWC(wcCoord, bool display = false);
        wcCoord changeToViewCoordinate(wcCoord);
        void changeToViewCoordinate();
        void drawLine(Uint32, wcCoord, wcCoord);
        void drawCircle(Uint32, wcCoord);
        void generateWC3D();

        vector<wcCoord> tempPoly;
        void triangleBegin();
        void trianglePoint(wcCoord);
        void triangleEnd();
        void renderWiredFrame();
        void scanLine();

        void setFrameRate(int);

        void eventHandler();
        void flipScreen();


        void matrixMul3X3(float dest[][3], float a[][3], float b[][3]);
        void matrixMul3X1(float dest[3][1], float a[3][3], float b[3][1]);
        void matrixMul4X4(float dest[4][4], float a[4][4], float b[4][4]);
        void matrixMul4X1(float dest[4][1], float a[4][4], float b[4][1]);

        bool getDone();

        void sandBox();
        void sphere();
        void cylinder();
        void torus();
        void passArray(float mat[][3]);
    private:
        SDL_Surface* screen;

        bool done;
        bool polyBegin;

        float initialTransMat[3][3];
        float viewPointMat[4][4];
        wcPoint viewerPos;
        float projectionMat[4][4];
        int vanisingPoint;
        float rotationMat[4][4];
        float finalMat[4][4];

        float tempMat4x1[4][1];
        float tempMat4x4[4][4];

        float tempPoint2D[3][1];
        int frame;
        long startTime, endTime;


        vector<wcCoord> vertexTable;
        vector<wcCoord> finalVertex;
        vector<wcCoord>::iterator vertexIter;
        vector<Edge> edgeTable;
        vector<Polygon> polygonTable;
        vector<Triangle> triangleTable;

        unsigned int addVertex(wcCoord);
        unsigned int addEdge(Edge);
        void addPolygon(Polygon);
        void testDisplay();

};
