#include "library.h"

void display4X4(float mat[4][4]){
    for (int i = 0; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            cout <<mat[i][j] << "  ";
        }
        cout << endl;
    }
}
void display4X1(float mat[4][1]){
    for (int i = 0; i < 4 ; i++){
        cout <<mat[i][0]<<endl;
    }
}


graphicsLibrary::graphicsLibrary(){
    initializeSDL();
    loadScreen();
    loadInitialTransMat();
    rotatex(0);
    done = false;
    startTime = SDL_GetTicks();
    frame = 0;
}
graphicsLibrary::~graphicsLibrary(){
    cleanUpMesh();
}


bool graphicsLibrary::initializeSDL(){  //initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    return true;
}

bool graphicsLibrary::loadScreen(){     //load new window
    screen = SDL_SetVideoMode(640, 480, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void graphicsLibrary::loadInitialTransMat(){    //loads initial translate Matrix
    float translateMat[3][3] = {1, 0, 320,
                            0, 1, 240,
                            0, 0, 1,
                        };
    float reflectXMat[3][3] = {1, 0, 0,
                            0, -1, 0,
                            0, 0, 1,
                        };
    matrixMul3X3(initialTransMat, translateMat, reflectXMat);
//    int sz = sizeof(initialTransMat)/sizeof(**initialTransMat);
//    std::copy(*temp, (*temp) + sz, *initialTransMat);       //copy(firstIterator, lastIterator, outputDest)
}

void graphicsLibrary::cleanUpMesh(){    //final shutdown cleans
    printf("All meshes have been cleaned");
}

void graphicsLibrary::rotatez(float angle){
    float tempMat[4][4] = {cos(angle*3.1415/180), -sin(angle*3.1415/180), 0, 0,
                            sin(angle*3.1415/180), cos(angle*3.1415/180), 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1

    };
    int sz = sizeof(rotationMat)/sizeof(**rotationMat);
    std::copy(*tempMat, (*tempMat) + sz, *rotationMat);
}

void graphicsLibrary::rotatex(float angle){
    float tempMat[4][4] = {1, 0, 0, 0,
                            0, cos(angle*3.1415/180), -sin(angle*3.1415/180), 0,
                            0, sin(angle*3.1415/180), cos(angle*3.1415/180), 0,
                            0, 0, 0, 1

    };
    int sz = sizeof(rotationMat)/sizeof(**rotationMat);
    std::copy(*tempMat, (*tempMat) + sz, *rotationMat);
}

void graphicsLibrary::rotatey(float angle){
    float tempMat[4][4] = {cos(angle*3.1415/180), 0, sin(angle*3.1415/180), 0,
                            0, 1, 0, 0,
                            -sin(angle*3.1415/180), 0, cos(angle*3.1415/180), 0,
                            0, 0, 0, 1

    };
    int sz = sizeof(rotationMat)/sizeof(**rotationMat);
    std::copy(*tempMat, (*tempMat) + sz, *rotationMat);
}

void graphicsLibrary::setViewPoint(wcCoord pos, int pRef){        //sets viewerPos and finally viewPoint Matrix
    viewerPos = {pos.x, pos.y, pos.z};
    vanisingPoint = pRef;
    updateViewPointMat();
    updateProjectionMat();

    matrixMul4X4(finalMat, projectionMat, viewPointMat);

    cout<<"projection matrix"<<endl;
    display4X4(projectionMat);
    cout<<"viewing point matrix"<<endl;
    display4X4(viewPointMat);

    wcPoint n = {viewerPos.x, viewerPos.y, viewerPos.z};//lookdirection
//    wcPoint n = {0, 0, 1};
    n.reduceToUnit();
    cout<<"normal vector"<<n.x<<" "<<n.y<<" "<<n.z<<endl;

    wcPoint V = {0,1,0};
    wcPoint u = V*n;
    u.reduceToUnit();
    wcPoint v = n*u;
    cout<<"u vector"<<u.x<<" "<<u.y<<" "<<u.z<<endl;
    cout<<"v vector"<<v.x<<" "<<v.y<<" "<<v.z<<endl;

    cout << "Viewpoint set to "<<pos.x<<" "<<pos.y<< " "<<pos.z<<" vanishing point set to "<<vanisingPoint<<endl;
}

void graphicsLibrary::updateViewPointMat(){        //sets viewPointMat, lookat points to origin
    wcPoint n = {viewerPos.x, viewerPos.y, viewerPos.z};
    n.reduceToUnit();
    wcPoint V = {0,1,0};
    wcPoint u = V*n;
    wcPoint v = n*u;
    float tempMat4x4[4][4] = { u.x, u.y, u.z, 0,
                                v.x, v.y, v.z, 0,
                                n.x, n.y, n.z, 0,
                                0, 0, 0, 1
                            };
    float tMat[4][4] = { 1, 0, 0, -viewerPos.x,
                            0, 1, 0, -viewerPos.y,
                            0, 0, 1, -viewerPos.z,
                            0, 0, 0, 1
    };
    float tempMat[4][4];
    matrixMul4X4(tempMat,tempMat4x4, tMat);
    int sz = sizeof(viewPointMat)/sizeof(**viewPointMat);
    std::copy(*tempMat, (*tempMat) + sz, *viewPointMat);
}

void graphicsLibrary::updateProjectionMat(){        //sets oblique projection matrix
    float tempMat[4][4] = {1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, -viewerPos.z/(vanisingPoint - viewerPos.z), viewerPos.z * vanisingPoint/(vanisingPoint - viewerPos.z),
                            0, 0, -1/(vanisingPoint - viewerPos.z), vanisingPoint/(vanisingPoint - viewerPos.z)

    };
    int sz = sizeof(projectionMat)/sizeof(**projectionMat);
    std::copy(*tempMat, (*tempMat) + sz, *projectionMat);

}

void graphicsLibrary::drawPixel(/*SDL_Surface *screen,*/ Uint32 color, int x, int y){    //draw pixel at position x, y and color specified by uint32
//    Uint32 color = SDL_MapRGB(screen->format, R, G, B);
    float temp[3][1] = {x, y, 1};
    matrixMul3X1(tempPoint2D, initialTransMat, temp);
    x = tempPoint2D[0][0];
    y = tempPoint2D[1][0];
//    if (x < 0 or x> 640 or y < 0 or y > 480)
//        return;

    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            return;
        }
    }
    switch (screen->format->BytesPerPixel) {
        case 1: { /* Assuming 8-bpp */
            Uint8 *bufp;

            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *bufp = color;
        }
        break;

        case 2: { /* Probably 15-bpp or 16-bpp */
            Uint16 *bufp;

            bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
            *bufp = color;
        }
        break;

        case 3: { /* Slow 24-bpp mode, usually not used */
//            Uint8 *bufp;
//
//            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
//            *(bufp+screen->format->Rshift/8) = R;
//            *(bufp+screen->format->Gshift/8) = G;
//            *(bufp+screen->format->Bshift/8) = B;
        }
        break;

        case 4: { /* Probably 32-bpp */
            Uint32 *bufp;

            bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
            *bufp = color;
        }
        break;
    }
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
    SDL_UpdateRect(screen, x, y, 1, 1);
}

wcCoord graphicsLibrary::changeToViewCoordinate(wcCoord pos){       //changes world coordinate to viewing coordinates
    float tempMat[4][1] = {pos.x, pos.y, pos.z, 1};
//    matrixMul4X1(tempMat4x1, viewPointMat, tempMat);
    matrixMul4X4(tempMat4x4, finalMat, rotationMat);
    matrixMul4X1(tempMat4x1, tempMat4x4, tempMat);
    pos.x = tempMat4x1[0][0]/tempMat4x1[3][0];
    pos.y = tempMat4x1[1][0]/tempMat4x1[3][0];
    pos.z = tempMat4x1[2][0]/tempMat4x1[3][0];
    return pos;
}

void graphicsLibrary::drawWC(wcCoord pos, bool display){        //draws World Coordinate to viewing plane
    pos = changeToViewCoordinate(pos);
//    if (display) display4X1(tempMat);
    drawPixel(COLOR_WHITE, pos.x, pos.y);

}

void graphicsLibrary::drawLine(Uint32 color, wcCoord initial, wcCoord final){   // draws line using Bresenham's Algorithm
    initial = changeToViewCoordinate(initial);
    final = changeToViewCoordinate(final);

    //Bresenham's Algorithm
    bool slopeMoreThan1 = false;
    if (fabs(final.y-initial.y)>fabs(final.x-initial.x)){
        float temp;
        temp = initial.x;
        initial.x = initial.y;
        initial.y = temp;

        temp = final.x ;
        final.x = final.y;
        final.y = temp;
        slopeMoreThan1 = true;
    }
    float dx = final.x-initial.x;
    float dy = final.y-initial.y;
    float yInc;
    float x, y, xDest;
    float p;

    yInc = (dx*dy>0)?1:-1;

    dx = fabs(dx);
    dy = fabs(dy);

    if (initial.x>final.x){
        x = final.x;
        y = final.y;
        xDest = initial.x;
    }else{
        x = initial.x;
        y = initial.y;
        xDest = final.x;
    }
    p = 2*dy-dx;
    do{
        if (slopeMoreThan1) drawPixel(COLOR_WHITE, y, x);
        else drawPixel(COLOR_WHITE, x,y);
        x++;
        if (p<0){
            p += 2*dy;
        }else{
            y += yInc;
            p += 2*dy -2*dx;
        }
    }while(x<=xDest);

    {
//    float dx = fabs(final.x-initial.x);
//    float dy = fabs(final.y-initial.y);
//
//    int error = dx-dy;
//    int e2;
//    float xInc, yInc;
//
//    xInc = (initial.x < final.x)?1:-1;
//    yInc = (initial.y < final.y)?1:-1;
//
//    do{
//        drawPixel(COLOR_WHITE, initial.x, initial.y);
//        e2 = 2*error;
//        if (e2 > -dy){
//            error -= dy;
//            initial.x += xInc;
//        }
//        if(e2 < dx){
//            error += dx;
//            initial.y += yInc;
//        }
//
//        if ((xInc == 1 and yInc == 1 and initial.x >= final.x and initial.y>= final.y) or
//            (xInc == 1 and yInc == -1 and initial.x >= final.x and initial.y<= final.y) or
//            (xInc == -1 and yInc == -1 and initial.x <= final.x and initial.y<= final.y) or
//            (xInc == -1 and yInc == 1 and initial.x <= final.x and initial.y>= final.y)
//            ) break;        // breaking conditions equal le kam deyena teyhi bhayera 4 wota conditions rakheko
//    }while(true);
    }
}

//void graphicsLibrary::drawCircle(Uint32 color, int x, int y, int radius){          //not completed
//}
//
void graphicsLibrary::generateWC3D(){                   // for temporary testing
    wcCoord temp(0,0,0);
    for (temp.x = -320 ; temp.x < 320 ; temp.x++){
        drawWC(temp);
    }
    temp.x = 0;
    for (temp.y = -240 ; temp.y < 240 ; temp.y++){
        drawWC(temp);
    }
    temp.y = 0 ;
    for (temp.z = -240 ; temp.z < 240 ; temp.z++){
        drawWC(temp);
    }
}




void graphicsLibrary::eventHandler(){   //event handlers
        SDL_Event event;
        wcCoord temp;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            done = true;
                            break;
                        case SDLK_LEFT:
                            temp = {viewerPos.x-5, viewerPos.y, viewerPos.z};
                            setViewPoint(temp, vanisingPoint);
                            break;
                        case SDLK_RIGHT:
                            temp = {viewerPos.x+5, viewerPos.y, viewerPos.z};
                            setViewPoint(temp, vanisingPoint);
                            break;
                        case SDLK_UP:
                            temp = {viewerPos.x, viewerPos.y+5, viewerPos.z};
                            setViewPoint(temp, vanisingPoint);
                            break;
                        case SDLK_DOWN:
                            temp = {viewerPos.x, viewerPos.y-5, viewerPos.z};
                            setViewPoint(temp, vanisingPoint);
                            break;
                        case SDLK_z:
                            temp = {viewerPos.x, viewerPos.y, viewerPos.z-5};
                            setViewPoint(temp, vanisingPoint);
                            break;
                        case SDLK_x:
                            temp = {viewerPos.x, viewerPos.y, viewerPos.z+5};
                            setViewPoint(temp, vanisingPoint);
                            break;
                        case SDLK_c:
                            temp = {viewerPos.x, viewerPos.y, viewerPos.z};
                            setViewPoint(temp, vanisingPoint-5);
                            break;
                        case SDLK_v:
                            temp = {viewerPos.x, viewerPos.y, viewerPos.z};
                            setViewPoint(temp, vanisingPoint+5);
                            break;
                        default:
                            break;
                    }
                }
            } // end switch
        } // end of message processing
}


bool graphicsLibrary::getDone(){            //for main loop
    return done;
}

void graphicsLibrary::flipScreen(){         //implementation of sdl_flip
    SDL_FillRect(screen, NULL, 0x000000);
    SDL_Flip(screen);
}


void graphicsLibrary::matrixMul3X3(float dest[][3], float a[3][3], float b[3][3]){
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            dest[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
        }
    }
}

void graphicsLibrary::matrixMul3X1(float dest[3][1], float a[3][3], float b[3][1]){
    for  (int i = 0 ; i < 3 ; i++){
        dest[i][0] = a[i][0] * b[0][0] + a[i][1] * b[1][0] + a[i][2] * b[2][0];
    }
}

void graphicsLibrary::matrixMul4X4(float dest[4][4], float a[4][4], float b[4][4]){
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            dest[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j];
        }
    }
}

void graphicsLibrary::matrixMul4X1(float dest[4][1], float a[4][4], float b[4][1]){
    for  (int i = 0 ; i < 4 ; i++){
        dest[i][0] = a[i][0] * b[0][0] + a[i][1] * b[1][0] + a[i][2] * b[2][0] + a[i][3]*b[3][0];
    }
}


void graphicsLibrary::setFrameRate(int fps){
    long timeDiff = SDL_GetTicks()-startTime;
    frame++;
    float frameRate = (frame*1000/timeDiff);
    cout<<frameRate<<endl;
}

unsigned int graphicsLibrary::addVertex(wcCoord aPoint){
    //if not previously in the vertex list then
    //    add it to the list and return the pointer
    //else
    //    return the presenting list
    int num = vertexTable.size();
    for (int i = 0; i < num ; i++){
        if (aPoint == vertexTable[i])
            return i;
    }
    vertexTable.push_back(aPoint);
    return num;
}
unsigned int graphicsLibrary::addEdge(Edge aEdge){/// not tested
    int num = edgeTable.size();
    for (int i = 0 ; i < num ; i++){
        if (aEdge == edgeTable[i])
            return i;
    }
    edgeTable.push_back(aEdge);
    return num;
}
void graphicsLibrary::addPolygon(Polygon aPoly){///not tested
    polygonTable.push_back(aPoly);
}

//Hit and Trial arena
void graphicsLibrary::testDisplay(){
    cout<<"Vertex Table"<<endl;
    for (int i = 0 ; i<vertexTable.size() ; i++){
        cout<<vertexTable[i].x<<" "<<vertexTable[i].y<<" "<<vertexTable[i].z<<" "<<i<<endl;
    }
    cout<<"Edge table"<<endl;
    for (int i = 0 ; i<edgeTable.size() ; i++){
        cout<<edgeTable[i].iCoord<<" "<<edgeTable[i].fCoord<<" "<<i<<endl;
    }
    cout<<"Polygon table"<<endl;
    for (int i = 0 ; i<polygonTable.size() ; i++){
        cout<<polygonTable[i].first<<" "<<polygonTable[i].second<<" "<<polygonTable[i].third<<" "<<&polygonTable[i]<<endl;
    }
}


void graphicsLibrary::sandBox(){
//    sphere();
//    cylinder();
    torus();



//    addEdge(Edge(addVertex(wcCoord(0,0,0)),addVertex(wcCoord(0,10,0))));
//    addEdge(Edge(addVertex(wcCoord(10,10,0)), addVertex(wcCoord(10,0,0))));
//    addEdge(Edge(addVertex(wcCoord(0,0,0)),addVertex(wcCoord(0,10,0))));
//
//
//    wcCoord a(180,0,0),b(90,10,0);
//    Edge e1(addVertex(a),addVertex(b));
//    addEdge(e1);
//
//    testDisplay();

//    addEdge(Edge(addVertex(wcCoord(70,0,0)),addVertex(wcCoord(0,170,0))));
//    addEdge(Edge(addVertex(wcCoord(160,10,0)), addVertex(wcCoord(160,0,0))));
//    addEdge(Edge(addVertex(wcCoord(70,0,0)),addVertex(wcCoord(0,170,0))));
//    addVertex(wcCoord(0,10,0));
//    testDisplay();
}

void graphicsLibrary::sphere(){
    vertexTable.clear();
    wcCoord temp;

    int vSlice = 10 ;
    int hSlice = 10 ;
    int radius = 50 ;

    float dPhi = 360 / vSlice;
    float dTheta = 360 / hSlice;

    for (int j = 0 ; j < hSlice ; j++ ){
        for (int i = 0 ; i < vSlice ; i++){
            temp.x = radius * cos(dPhi * i * 3.1415 / 180) * cos(dTheta * j * 3.1415 / 180);
            temp.y = radius * sin(dPhi * i * 3.1415 / 180) * cos(dTheta * j * 3.1415 / 180);
            temp.z = radius * sin(dTheta * j * 3.1415 / 180);
            vertexTable.push_back(temp);
        }
    }
    int n = vertexTable.size();
    for (int j = 0 ; j< hSlice ; j++){
        for (int i = 0 ; i < vSlice ; i++ ){
            drawLine(COLOR_WHITE, vertexTable[j*hSlice+i], vertexTable[j*hSlice+i+1]);
            if (j != hSlice-1) drawLine(COLOR_WHITE, vertexTable[j*hSlice+i], vertexTable[j*hSlice+i+vSlice]);
        }
    }
//    for (int i = 0; i < n-2 ; i++){
//        drawLine(COLOR_WHITE, vertexTable[i], vertexTable[i+1]);
//    }
}

void graphicsLibrary::cylinder(){
    vertexTable.clear();
    wcCoord temp;

    int vSlice = 10 ;
    int hSlice = 5 ;
    int radius = 50 ;
    int height = 100 ;

    float dPhi = 360 / vSlice;
    float dBlock = height / hSlice;

    for (int j = 0 ; j < hSlice ; j++ ){
        for (int i = 0 ; i < vSlice ; i++){
            temp.x = radius * cos(dPhi * i * 3.1415 / 180);
            temp.y = radius * sin(dPhi * i * 3.1415 / 180);
            temp.z = dBlock * j;
            vertexTable.push_back(temp);
        }
    }
    int n = vertexTable.size();
    for (int j = 0 ; j< hSlice ; j++){
        for (int i = 0 ; i < vSlice-1 ; i++ ){
            drawLine(COLOR_WHITE, vertexTable[j*hSlice+i], vertexTable[j*hSlice+i+1]);
            if (j != hSlice-1) drawLine(COLOR_WHITE, vertexTable[j*hSlice+i], vertexTable[j*hSlice+i+vSlice]);
        }
    }
//    for (int i = 0; i < n-1 ; i++){
//        for(int j = 0 ; j < vSlice-1 ; i++,j++)
//            drawLine(COLOR_WHITE, vertexTable[i], vertexTable[i+1]);
//        drawLine(COLOR_WHITE, vertexTable[i-vSlice], vertexTable[i]);
//    }
}

void graphicsLibrary::torus(){
    vertexTable.clear();
    wcCoord temp;

    int vSlice = 25;
    int hSlice = 25 ;

    //if c>a its a doughnut/ring torus
    //if c==a its a horn torus
    //c<a spindle torus
    int rTorus = 100 ;   //c
    int rTube = 50;     //a

    float dPhi = 360 / vSlice;
    float dTheta = 360 / hSlice;


    for (int j = 0 ; j < hSlice ; j++ ){
        for (int i = 0 ; i < vSlice ; i++){
            temp.x = ( rTorus + rTube * cos(dPhi * i * 3.1415 / 180 - 3.1415)) * cos(dTheta * j * 3.1415 / 180 - 3.1415);
            temp.y = ( rTorus + rTube * cos(dPhi * i * 3.1415 / 180 - 3.1415)) * sin(dTheta * j * 3.1415 / 180 - 3.1415);
            temp.z = rTube * sin(dPhi * i * 3.1415 / 180 - 3.1415);
            vertexTable.push_back(temp);
        }
    }
    int n = vertexTable.size();
    for (int j = 0 ; j< hSlice ; j++){
        for (int i = 0 ; i < vSlice ; i++ ){
//            drawLine(COLOR_WHITE, vertexTable[j*hSlice+i], vertexTable[j*hSlice+i+1]);
//            if (j != hSlice-1) drawLine(COLOR_WHITE, vertexTable[j*hSlice+i], vertexTable[j*hSlice+i+vSlice]);
            drawWC(vertexTable[j*hSlice+i]);
        }
    }
//    for (int i = 0; i < n-2 ; i++){
//        drawLine(COLOR_WHITE, vertexTable[i], vertexTable[i+1]);
//    }
}

void graphicsLibrary::passArray(float mat[][3]){
    for ( int i = 0 ; i<3 ; i++){
        for ( int j = 0 ; j<3 ; j++){
            cout<<mat[i][j];
        }
    }
    printf("done");
}
