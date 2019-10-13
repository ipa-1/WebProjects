#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <iostream>
using namespace std; 

// My imported libraries
#include <math.h>
#include "mathLib2D.h"
#include <vector>  // for vector 


// Window Coordinates Default
int gWidth = 700;
int gHeight = 700;


//Global Variables
float gRange = 1000; // range 
float gSpeed = 1; // speed 
Point2D m; // mouse position
bool leftMouse; // indicates if left mouse is clicked
bool pause = false; // melt animation status
vector <Particle> pList; // holds particles that are displayed on window

//Function that creates a random generation of particles on the screen
void genParticles(){
    int totalParticles = rand()% 500 + 300; // Randomizing total number of particles on screen
    //int totalParticles = 100; // Testing value
    Particle p;
    colour c;
    int s;
    Point2D pl;

    for (int i = 0; i < totalParticles; i++){ // 
        pl = Point2D(rand() %(gWidth*10),rand() %(gHeight*10)); // randomizing location
        //range = ((50.0 - 20.0) * ((float)rand() / RAND_MAX)) + 20.0; float range
        c = colour(rand() %2,rand() %2,rand() %2); // randomizing colour
        s = rand() % 5 + 5; // randomizing size
        p = Particle(pl,c, s,Vec2D(0,0),gRange,gSpeed);
        pList.push_back(p);
    }
}

//Function that adds particles to a global vector
void addParticle(int x, int y){
    colour c = colour(rand() %2,rand() %2,rand() %2); // randomizing colour get<0>(c)
    int s = rand() % 5 + 5; // randomizing size
    Point2D newP = Point2D(x,y);
    Particle p = Particle(newP,c, s,Vec2D(0,0),gRange,gSpeed);
    pList.push_back(p);     
}

//Function that generates lines by increasing x by increments
void genLines(){
    pList.clear();
    int x = 50; // Starting from the top of the screen
    int y = 50;

    while (y < (gHeight*10)){ // While you are not at the bottom of the screen
        while(x < (gWidth*10)){ // Move across the screen and add particles
            x+=50;
            addParticle(x,y);
        }
        y+=500;
        x=0;
    }
}

/* TODO: shape that makes circles around center of window*/
void genCircle(){
    int x = (gWidth*10)/2;
    int y = (gHeight*10)/2;
    addParticle(x,y); // generates a point in the middle
}

//Function that uses a sin function to create waves by increasing x by increments
void genTrig(){
    pList.clear();
    int x = 0; // is the value we will increase to get across the screen
    int y = (gHeight*10)/2; // is the value we will change to get the wave

    //For loop to generate the waves in levels
    while(x < gWidth*10){
        x+=50; // Increase this to decrease the density of the particles
        for (int i = -5; i < 5; i++){
           addParticle(x,y+400*sin(0.005*x)+ i*1000); 
        }
    }
}


//Delete particle function
void delParticle(int x, int y){
    int index = 0; 
    Point2D delP = Point2D(x,y);
    int mDistance = delP.distanceTo(pList[0].location); 
    int cDistance;

    for (int i = 0; i < pList.size(); i++){
        cDistance = delP.distanceTo(pList[i].location);
        //std::cout << pList[i].location.mX<< " " <<pList[i].location.mY<< ": " << cDistance << std::endl;
        if (cDistance < mDistance){ // if distance of particle in list currently is closer
            index = i; // then keep track of the index of this particle
            mDistance = cDistance; // update minimum distance variable
            //std::cout << "Closest: " << pList[i].location.mX<< " " <<pList[i].location.mY << std::endl;
        }
    }
    pList.erase(pList.begin() + index);
}

// Function that displays particles in particle list
void displayParticle(){
    for (int i = 0; i < pList.size(); i++){
        glColor3f(get<0>(pList[i].mC),get<1>(pList[i].mC),get<2>(pList[i].mC));
        glPointSize(pList[i].size); // this must be before glBegin or it will not work
        glBegin(GL_POINTS);
            glVertex3f(pList[i].location.mX ,pList[i].location.mY,0); 
        glEnd();
    }
}

//Function that updates the range in all particle
void updateRange(){  
    for (int i = 0; i < pList.size(); i++){
        pList[i].range = gRange;
    }
}

//Function that updates the speed in all particles
void updateSpeed(){  
    for (int i = 0; i < pList.size(); i++){
        pList[i].speed = gSpeed;
    }
}

// Handler for special keys
void special(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP: // increases speed

            if (gSpeed <15){
               gSpeed+=0.5; 
            }
            //std::cout << "Speed "<< gSpeed << std::endl;
            updateSpeed();
            break;

        case GLUT_KEY_DOWN: // decreases speed
            if (gSpeed > 1.5){
               gSpeed-=0.5; 
            }
            //std::cout << "Speed "<< gSpeed << std::endl;
            updateSpeed();
            break;
    }
}

//Function that performs function when menu item is clicked
void menuProc(int value){
    if (value == 1){
        genLines();
        displayParticle();
    }
    if (value == 2)
        genTrig();
        displayParticle();
    if (value == 3)
        pause = false;
    if (value == 4)
        pause = true;
    if (value == 5)
        genCircle();
        displayParticle();
}

//Creates the menu
void createOurMenu(){
    int subMenu_id = glutCreateMenu(menuProc);
    glutAddMenuEntry("Pause", 3);
    glutAddMenuEntry("Unpause", 4);
    
    int main_id = glutCreateMenu(menuProc);
    glutAddMenuEntry("Lines Shape", 1);
    glutAddMenuEntry("Wave Shape", 2);
    glutAddMenuEntry("Circle Shape", 5);
    glutAddSubMenu("Pause", subMenu_id);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

/* display function - GLUT display callback function
 *      clears the screen, draws stuff, and displays it
 */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); 

        glBegin(GL_POINTS);
            displayParticle();
        glEnd();

    //glFlush(); // pushes all the above operations to OpenGL to be exeucted/displayed
    glutSwapBuffers(); //swap buffers - rendering is done to the back buffer, bring it forward to display
    glutPostRedisplay(); //force a redisplay, to keep the animation running
}

//Function that handles moving particles closer or farther from mouse position
void move(bool closer){
    for (int i = 0; i < pList.size(); i++){

        if (m.distanceTo(pList[i].location)< gRange){
            //std::cout <<"Distance to mouse: " << m.distanceTo(pList[i].location) <<std::endl; 
            
            if (closer){ // move away from m
                pList[i].direction = pList[i].direction.createVector(m,pList[i].location);
            }

            else{ // move closer to m
                pList[i].direction = pList[i].direction.createVector(pList[i].location,m);
            }

            pList[i].direction = pList[i].direction.normalize();
            pList[i].direction = pList[i].direction.multiply(gSpeed);

            //Checking bounds, moving particle to opposite side if it is being pushed to edge
            if (pList[i].location.mX > gHeight*10){
                pList[i].location.mX = 0;
            }
            if (pList[i].location.mY > gWidth*10){
                pList[i].location.mY = 0;
            }
            if (pList[i].location.mX < 0){
                pList[i].location.mX = gHeight*10;
            }
            if (pList[i].location.mY < 0){
                pList[i].location.mY = gWidth*10;
            }

            pList[i].location = pList[i].direction.movePoint(pList[i].location); 
        }
    }
}

/* TODO: make particles move in a circle around the origin
void spin(){
    if (!pause){

        Point2D center = Point2D(gWidth/2,gHeight/2)

        for (int i = 0; i < pList.size(); i++){

            if (m.distanceTo(pList[i].location)< gRange){
                //std::cout <<"Distance to mouse: " << m.distanceTo(pList[i].location) <<std::endl; 
                
                
                if (closer){ // move away from m
                    pList[i].direction = pList[i].direction.createVector(m,pList[i].location);
                }

                else{ // move closer to m
                    pList[i].direction = pList[i].direction.createVector(pList[i].location,m);
                }

                pList[i].direction = pList[i].direction.normalize();
                pList[i].direction = pList[i].direction.multiply(gSpeed);
                //std::cout <<"vec: " << pList[i].direction.mX << " " << pList[i].direction.mY <<std::endl;
                pList[i].location = pList[i].direction.movePoint(pList[i].location); 
            }
        }

    }
}*/

//Function that makes the particles "melt" on the screen
void melt(){
    for (int i = 0; i < pList.size(); i++){

        Point2D bot = Point2D(pList[i].location.mX,gHeight*10);

        if (pList[i].location.mY < gHeight*10){
            pList[i].direction = pList[i].direction.createVector(pList[i].location,bot);
            pList[i].direction = pList[i].direction.normalize();
            //pList[i].direction = pList[i].direction.multiply(2);
            pList[i].location = pList[i].direction.movePoint(pList[i].location); 
        }
        else{
            pList[i].location.mY = 0;
        }
    }
}

//Function that merges particles if they are within a range
void merge(){

    Particle p1;
    Particle p2;
    int newSize;
    colour c;
    Particle p;

    for (int i = 0; i < pList.size(); i++){
        p1 = pList[i];
        for (int j = 0; j < pList.size(); j++){
            p2 = pList[j];
            if (((i != j) && (p1.mC == p2.mC))&& ((p1.location).distanceTo(p2.location) < 200)) {
                newSize = p1.size+5;
                pList.erase(pList.begin() + i);
                pList.erase(pList.begin() + j);
                c = colour(get<0>(p1.mC),get<1>(p1.mC),get<2>(p1.mC)); 
                p = Particle(p1.location,c, newSize,Vec2D(0,0),gRange,gSpeed);
                pList.push_back(p); 
            }
        }  
    }  
}

/* TODO: Function where when mouse clicked, moves particles in range away
void separate(){
    for (int i = 0; i < pList.size(); i++){
        p1 = pList[i];

        if ((m.distanceTo(p1.location) < 200)) {
                newSize = p1.size+5;
                pList.erase(pList.begin() + i);
                pList.erase(pList.begin() + j);
                c = colour(get<0>(p1.mC),get<1>(p1.mC),get<2>(p1.mC)); 
                p = Particle(p1.location,c, newSize,Vec2D(0,0),gRange,gSpeed);
                pList.push_back(p); 
        }
    } 
}*/

// TODO: make particles slow down if they were moving before
/*
void momentum(){
    for (int i = 0; i < pList.size(); i++){
        if (pList[i].speed < 0){
            pList[i].speed = 0;
        }
        else if (pList[i].speed > 0){
            pList[i].location = pList[i].direction.movePoint(pList[i].location);
            pList[i].speed -=1;
        }
    }
}*/


// Changes the colour of the particle if the mouse is within range
void mark(){
    for (int i = 0; i < pList.size(); i++){
        if(m.distanceTo(pList[i].location)< 100){
            pList[i].mC = colour(rand() %2,rand() %2,rand() %2);
            }
    }
}

//Idle function 
void idle(){
    if (pause == true ){
        melt();  
    }
    merge();
    //momentum();
    
}


//Keyboard handler
void kbd(unsigned char key, int x, int y){

    int mod = glutGetModifiers();
    switch(key){
        case ' ':
            pause = !pause;
            break;

        case 'q':
            exit(0);
            break;

        case 'a':
            addParticle(x*10,y*10);
            break;
        case 'r':
            pList.clear();
            genParticles();
            break;
        case 'd':
            delParticle(x*10,y*10);
            break;
        case '-':
            if (gRange > 500){
               gRange -=100; 
            }
            //std::cout << "Range update: " << gRange << std::endl;
            updateRange();
            break;
        case '=':
            if (gRange < 4000){
               gRange +=100;
            }
            //std::cout << "Range update: " << gRange << std::endl;
            updateRange();
            break;
        default:
            //std::cout << "Default Pressed: " << key << std::endl;
            break;
    }
    glutSwapBuffers(); 
    glutPostRedisplay();

}

// Mouse Handler for first press and first release
void mouse(int btn, int state, int x, int y){

        if (state == GLUT_UP){
            //std::cout << "Released\n";
            leftMouse = false;
        }
        if (state == GLUT_DOWN){
            if (btn == GLUT_LEFT_BUTTON){
                leftMouse = true;
            }
            else if (btn == GLUT_RIGHT_BUTTON){
                leftMouse = false;
            }
        }
}

void motion (int x, int y){ // Is called when you move while mouse is pressed
    //std::cout << "mouseMotion coords: ";
    //std:: cout << m.mX << ", " << m.mY;
    //std::cout << " mouseMotion coords2: ";
    //std:: cout << x << ", " << y << std::endl;
    m.mX = x*10; // update mouse coordinates
    m.mY = y*10;
    if (leftMouse){
        move(false);      
    }
    else{
        move(true);
    }
}

void passive (int x, int y){ // Is called when you move your mouse
    //std::cout << "passiveMotion coords: ";
    m.mX = x*10;
    m.mY = y*10;
    mark();
    //std:: cout << x << ", " << y << std::endl;
}

void reshape(int w, int h) // This changes the coordinate system, I think
{
    gWidth  = glutGet(GLUT_WINDOW_WIDTH);        //set global width
    gHeight = glutGet(GLUT_WINDOW_HEIGHT);        //set global height

    glMatrixMode(GL_PROJECTION); // ** 
    glLoadIdentity(); //  Reset what we had before
    gluOrtho2D(0, w, h, 0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h); // Glut view window calls glViewport, specifies width and height
}

//Init to create the menu
void init(void)
{
    createOurMenu();
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    if (!pause){
        melt();
    }
    //move(false);  
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
}

// Callback function
void callBackInit(){

    glutKeyboardFunc(kbd);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passive);
    glutIdleFunc(idle);
    glutDisplayFunc(display); //registers "display" as the display callback function
}

/* main function - program entry point */
int main(int argc, char** argv)
{

    gWidth = 700;
    gHeight = 700;
    glutInit(&argc, argv);      //starts up GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // Double buffering
    glutInitWindowSize(gWidth,gHeight);
    glutCreateWindow("Particles!!!");  //creates the window
    //srand (static_cast <unsigned> (time(0))); // seed the random number generator
    gluOrtho2D(-10,10,-10,10);

    //Commands for program
    std:: cout << "   Commands" << std::endl;
    std:: cout << "   q      quit" << std::endl;
    std:: cout << "   a      add new particle at mouse cursor" << std::endl;
    std:: cout << "   d      delete particle closest to mouse cursor" << std::endl;
    std:: cout << "   r      regenerate particles" << std::endl;
    std:: cout << "   -      decrease range" << std::endl;
    std:: cout << "   =      increase range" << std::endl;
    std:: cout << "   up     increase speed" << std::endl;
    std:: cout << "   down   decrease speed" << std::endl;
    
    std:: cout << " "<< std::endl;
    std:: cout << "   left mouse hold    attract particles" << std::endl;
    std:: cout << "   right mouse hold   repell particles" << std::endl;
    std:: cout << "   middle mouse click   open side menu" << std::endl;
    std:: cout << " "<< std::endl;

    std:: cout << "Bonus Features "<< std::endl;
    std:: cout << "   space  pause/start melt animation" << std::endl;
    std:: cout << "   Particles can combine" << std::endl;
    std:: cout << "   Hovering over particles can make them change colours" << std::endl;
    std:: cout << "   Side menu has options for generated shapes such as line/wave";
    createOurMenu();
    genParticles();
    callBackInit();
    init();
    glutMainLoop();             //starts the event loop
    return(0);                  //return may not be necessary on all compilers
}

