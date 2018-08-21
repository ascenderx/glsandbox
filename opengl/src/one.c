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
boolean init    (void);
void    input   (void * dummy);
void    update  (void * dummy);
void    render  (void * dummy);
void    cleanUp (void * dummy);

struct Point2f gPts1[] = {
    {0, 0}, {100, 100}, {50, 75}
};
struct Path2f gPolygon1 = {3, gPts1};

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
    if (!utilInitEngine()) {
        return FALSE;
    }

    utilWinWidth    = 400;
    utilWinHeight   = 400;
    utilWinTitle    = "GLSandbox #1";
    utilFramerate   = 30;
    utilBGColor     = 0x000000;
    utilUserInput   = input;
    utilUserUpdate  = update;
    utilUserRender  = render;
    utilUserCleanUp = cleanUp;

    return TRUE;
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
    utilStrokePolygon2D(&gPolygon1);
}

/****************************************************************************
 * 
 ****************************************************************************/
void cleanUp(void * dummy) {

}