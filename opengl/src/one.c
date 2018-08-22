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
#define WIN_WIDTH     400
#define WIN_HEIGHT    400
#define WIN_TITLE     "GLSandbox #1"
#define WIN_FRAMERATE 30
#define WIN_BG_COLOR  0x000000

/****************************************************************************
 * 
 ****************************************************************************/
struct Point2f gPts1[] = {
    {0, -10}, {-20, 20}, {20, 20}
};
struct Path2f gPolygon1 = {3, {WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0}, gPts1};

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

    utilSetWinDims(WIN_WIDTH, WIN_HEIGHT);
    utilSetWinTitle(WIN_TITLE);
    utilSetFramerate(WIN_FRAMERATE);
    utilSetBGColor(WIN_BG_COLOR);
    utilSetTickFunc(tick);

    return TRUE;
}

/****************************************************************************
 * 
 ****************************************************************************/
#define WASD_SPEED   5.0
#define ROTATE_SPEED 5.0
void input(void) {
    float dx = 0.0;
    float dy = 0.0;
    float dr = 0.0;

    if (utilIsKeyDown(GLFW_KEY_LEFT)) {
        dx = -WASD_SPEED;
    } else if (utilIsKeyDown(GLFW_KEY_RIGHT)) {
        dx = +WASD_SPEED;
    }

    if (utilIsKeyDown(GLFW_KEY_UP)) {
        dy = -WASD_SPEED;
    } else if (utilIsKeyDown(GLFW_KEY_DOWN)) {
        dy = +WASD_SPEED;
    }

    if (utilIsKeyDown(GLFW_KEY_A)) {
        dr = -ROTATE_SPEED;
    } else if (utilIsKeyDown(GLFW_KEY_D)) {
        dr = +ROTATE_SPEED;
    }

    if (dx || dy) {
        utilTranslatePolygon(&gPolygon1, dx, dy);
    }
    
    if (dr) {
        utilRotatePolygonAboutCenter(&gPolygon1, dr);
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
    utilStrokePolygon(&gPolygon1);

    utilSetColor(0xff0000);
    utilFillPoint(&gPolygon1.center);
}

/****************************************************************************
 * 
 ****************************************************************************/
void cleanUp(void) {

}