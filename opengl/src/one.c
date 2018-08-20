/****************************************************************************
 * 
 ****************************************************************************/
#include "../include/utiltypes.h"
#include "../include/utilinit.h"
#include "../include/utildraw.h"
#include "../include/utilinput.h"
#include "../include/utildebug.h"

/****************************************************************************
 * 
 ****************************************************************************/
boolean init(void);
void input(void * dummy);
void update(void * dummy);
void render(void * dummy);
void cleanUp(void * dummy);

struct Point2f pts1[] = {
    {0, 0}, {100, 100}, {50, 75}, {0, 0}
};
struct Path2f polygon = { 4, pts1 };

/****************************************************************************
 * 
 ****************************************************************************/
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
int main(int argc, char ** argv) {
    boolean initialized = init();
    if (!initialized) {
        return EXIT_FAILURE;
    }

    boolean success = utilMainLoop();
    return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean init(void) {
    uint winWidth   = 400;
    uint winHeight  = 400;
    char * winTitle = "GLSandbox #1";
    utilFramerate   = 30;
    utilBGColor     = 0x000000;

    utilInitEngine(winWidth, winHeight, winTitle);
    if (utilInitialized) {
        utilInit2DRenderer();

        utilUserInput   = input;
        utilUserUpdate  = update;
        utilUserRender  = render;
        utilUserCleanUp = cleanUp;
    }

    return utilInitialized;
}

/****************************************************************************
 * 
 ****************************************************************************/
void input(void * dummy) {
    
}

/****************************************************************************
 * 
 ****************************************************************************/
void update(void * dummy) {
    
}

/****************************************************************************
 * 
 ****************************************************************************/
void render(void * dummy) {
    utilClearScreen();
    utilSetColor(0x00ff00);
    utilPolyline2D(&polygon);
}

/****************************************************************************
 * 
 ****************************************************************************/
void cleanUp(void * dummy) {

}