/****************************************************************************
 * 
 ****************************************************************************/
#include "utiltypes.h"
#include "utilinit.h"
#include "utildraw.h"
#include "utilinput.h"
#include "utildebug.h"

/****************************************************************************
 * 
 ****************************************************************************/
void init(void);
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
    init();
    
    if (!utilInitialized) {
        return EXIT_FAILURE;
    }

    utilInit2DRenderer();

    boolean success = utilMainLoop();
    return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/****************************************************************************
 * 
 ****************************************************************************/
void init(void) {
    uint winWidth   = 400;
    uint winHeight  = 400;
    char * winTitle = "GLSandbox #1";
    utilFramerate   = 30;
    utilBGColor     = 0x000000;

    utilInitEngine(winWidth, winHeight, winTitle);

    utilUserInput   = input;
    utilUserUpdate  = update;
    utilUserRender  = render;
    utilUserCleanUp = cleanUp;
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