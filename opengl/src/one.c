/****************************************************************************
 * 
 ****************************************************************************/
#include <utiltypes.h>
#include <utilinit.h>
#include <utildraw.h>
#include <utilinput.h>
#include <utildebug.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "player.h"

/****************************************************************************
 * 
 ****************************************************************************/
void * init(void);
void   input(void * ptr);
void   update(void * ptr);
void   render(void * ptr);
void   tick(void * ptr);
void   cleanUp(void * ptr);

/****************************************************************************
 * 
 ****************************************************************************/
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
int main(int argc, char ** argv) {
    struct Player * player = init();
    
    if (!player) {
        return EXIT_FAILURE;
    }

    boolean success = utilMainLoop();
    cleanUp(player);
    return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/****************************************************************************
 * 
 ****************************************************************************/
void * init() {
    if (!utilInitEngine()) {
        return NULL;
    }

    // init user data
    struct Player * player = initPlayer();

    if (player) {
        utilSetWinDims(WIN_WIDTH, WIN_HEIGHT);
        utilSetWinTitle(WIN_TITLE);
        utilSetFramerate(WIN_FRAMERATE);
        utilSetBGColor(WIN_BG_COLOR);
        utilSetTickFunc(tick);
        utilSetUserData(player);
    }

    return player;
}

/****************************************************************************
 * 
 ****************************************************************************/
#define WASD_SPEED   5.0
#define ROTATE_SPEED 5.0
void input(void * ptr) {
    struct Player * player = (struct Player *) ptr;

    // defaults (in case not moving)
    float dx = 0.0;
    float dy = 0.0;
    float da = 0.0;

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
        da = -ROTATE_SPEED;
    } else if (utilIsKeyDown(GLFW_KEY_D)) {
        da = +ROTATE_SPEED;
    }

    player->velocity->dx = dx;
    player->velocity->dy = dy;
    player->degreesToRotateImage = da;
}

/****************************************************************************
 * 
 ****************************************************************************/
void update(void * ptr) {
    updatePlayer((struct Player *) ptr);
}

/****************************************************************************
 * 
 ****************************************************************************/
void render(void * ptr) {
    struct Player * player = (struct Player *) ptr;

    utilClearScreen();
    drawPlayer(player);

    // draw a point on the player's center
    utilSetColor(0xff0000);
    utilFillPoint(player->position);
}

/****************************************************************************
 * 
 ****************************************************************************/
void tick(void * ptr) {
    input(ptr);
    update(ptr);
    render(ptr);
}

/****************************************************************************
 * 
 ****************************************************************************/
void cleanUp(void * ptr) {
    releasePlayer((struct Player *) ptr);
}