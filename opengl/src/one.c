/****************************************************************************
 * 
 ****************************************************************************/
#include <stdlib.h> // *alloc, free

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
void * init(void);
void   input(void * ptr);
void   update(void * ptr);
void   render(void * ptr);
void   tick(void * ptr);
void   cleanUp(void * ptr);

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
struct Velocity2f {
    float dx;
    float dy;
};

/****************************************************************************
 * 
 ****************************************************************************/
struct Player {
    struct Path2f * image;
    struct Point2f * position;
    struct Velocity2f * velocity;
    float rotation;
    float direction;
    float degreesToRotateImage;
};

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
struct Point2f gPlayerPosition = {WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0};
struct Point2f gPlayerVertices[] = {{0, -10}, {-20, 20}, {20, 20}};
struct Path2f gPlayerImage = {3, &gPlayerPosition, gPlayerVertices};
struct Velocity2f gPlayerVelocity = {0.0, 0.0};
float gPlayerRotation = 0.0;
float gPlayerDirection = 0.0;
float gPlayerDA = 0.0;

/****************************************************************************
 * 
 ****************************************************************************/
void * init() {
    if (!utilInitEngine()) {
        return NULL;
    }

    // init user data
    struct Player * player = (struct Player *) malloc(sizeof(struct Player));
    player->image = &gPlayerImage;
    player->position = &gPlayerPosition;
    player->velocity = &gPlayerVelocity;
    player->rotation = gPlayerRotation;
    player->direction = gPlayerDirection;
    player->degreesToRotateImage = gPlayerDA;

    utilSetWinDims(WIN_WIDTH, WIN_HEIGHT);
    utilSetWinTitle(WIN_TITLE);
    utilSetFramerate(WIN_FRAMERATE);
    utilSetBGColor(WIN_BG_COLOR);
    utilSetTickFunc(tick);
    utilSetUserData(player);

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
    struct Player * player = (struct Player *) ptr;
    struct Velocity2f * vel = player->velocity;

    if (vel->dx || vel->dy) {
        player->position->x += vel->dx;
        player->position->y += vel->dy;
    }
    
    float dr = player->degreesToRotateImage;
    if (dr) {
        utilRotatePolygonAboutCenter(player->image, dr);
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void render(void * ptr) {
    struct Player * player = (struct Player *) ptr;

    utilClearScreen();

    utilSetColor(0x00ff00);
    utilStrokePolygon(player->image);

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

}