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
void    tick    (void * dummy);
boolean init    (void);
void    input   (void);
void    update  (void);
void    render  (void);
void    cleanUp (void);
void    movePolygon(struct Path2f * polygon, float dx, float dy);

/****************************************************************************
 * 
 ****************************************************************************/
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
    cleanUp();
    return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/****************************************************************************
 * 
 ****************************************************************************/
void tick(void * dummy) {
    input();
    update();
    render();
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean init(void) {
    if (!utilInitEngine()) {
        return FALSE;
    }

    utilSetWinDims(400, 400);
    utilSetWinTitle("GLSandbox #1");
    utilSetFramerate(30);
    utilSetBGColor(0x000000);
    utilSetTickFunc(tick);

    return TRUE;
}

/****************************************************************************
 * 
 ****************************************************************************/
#define WASD_SPEED 5
void input(void) {
    if (utilIsKeyDown(GLFW_KEY_LEFT)) {
        movePolygon(&gPolygon1, -WASD_SPEED, 0);
    } else if (utilIsKeyDown(GLFW_KEY_RIGHT)) {
        movePolygon(&gPolygon1, +WASD_SPEED, 0);
    }

    if (utilIsKeyDown(GLFW_KEY_UP)) {
        movePolygon(&gPolygon1, 0, -WASD_SPEED);
    } else if (utilIsKeyDown(GLFW_KEY_DOWN)) {
        movePolygon(&gPolygon1, 0, +WASD_SPEED);
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void update(void) {
    
}

/****************************************************************************
 * 
 ****************************************************************************/
void render(void) {
    utilClearScreen();
    utilSetColor(0x00ff00);
    utilStrokePolygon2D(&gPolygon1);
}

/****************************************************************************
 * 
 ****************************************************************************/
void cleanUp(void) {

}

/****************************************************************************
 * 
 ****************************************************************************/
void movePolygon(struct Path2f * polygon, float dx, float dy) {
    for (uint p = 0; p < polygon->length; p++) {
        polygon->points[p].x += dx;
        polygon->points[p].y += dy;
    }
}