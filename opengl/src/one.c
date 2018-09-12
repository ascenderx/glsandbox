/****************************************************************************
 * 
 ****************************************************************************/
#include <utiltypes.h>
#include <utilinit.h>
#include <utildraw.h>
#include <utilinput.h>
#include <utildebug.h>
#include <utiltext.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "one-player.h"

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
boolean gPaused;
boolean gPPressed;
boolean gShowCursor;
boolean gClicked;

/****************************************************************************
 * 
 ****************************************************************************/
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
int main(int argc, char ** argv) {
    struct Player * player = init();

    if (!player) {
        utilDebug("Error constructing player", ANSI_RED);
        return EXIT_FAILURE;
    }

    boolean success = utilMainLoop();
    cleanUp(player);
    return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/****************************************************************************
 * 
 ****************************************************************************/
#define GLYPH_MARGIN_X  0
#define GLYPH_MARGIN_Y  1
#define GLYPH_SCALING   6
#define GLYPH_TAB_WIDTH 4
void * init() {
    if (!utilInitEngine()) {
        utilDebug("Error initializing engine", ANSI_YELLOW);
        return NULL;
    }

    // init user data
    struct Player * player = initPlayer();

    if (player) {
        gPaused     = FALSE;
        gPPressed   = FALSE;
        gShowCursor = FALSE;
        gClicked    = FALSE;

        utilSetWinDims(WIN_WIDTH, WIN_HEIGHT);
        utilSetWinTitle(WIN_TITLE);
        utilSetFramerate(WIN_FRAMERATE);
        utilSetBGColor(WIN_BG_COLOR);
        utilSetTickFunc(tick);
        utilSetUserData(player);
        utilSetCursorVisible(gShowCursor);
        utilSetGlyphDims(GLYPH_MARGIN_X, GLYPH_MARGIN_Y, GLYPH_SCALING, GLYPH_TAB_WIDTH);
    }

    return player;
}

/****************************************************************************
 * 
 ****************************************************************************/
#define WASD_SPEED    10.0f
#define ROTATE_SPEED  5.0f
#define JOYSTICK      GLFW_JOYSTICK_1
#define JOY_AXIS_L    0
#define JOY_AXIS_R    1
#define JOY_DEAD_ZONE 0.10f
#define BT_PAUSE      9
void input(void * ptr) {
    struct Player * player = (struct Player *) ptr;
    
    if (utilKeys[GLFW_KEY_LEFT_CONTROL]) {
        if (utilKeys[GLFW_KEY_W] || utilKeys[GLFW_KEY_Q]) {
            utilEnd();
            return;
        }
    }

    struct Joystick * joystick = &utilJoysticks[JOYSTICK];
    boolean joyStartPressed = joystick->available && joystick->buttons[BT_PAUSE];
    if ((utilKeys[GLFW_KEY_P] || joyStartPressed) && !gPPressed) {
        gPaused = !gPaused;
        gPPressed = TRUE;
    } else if (!utilKeys[GLFW_KEY_P] && !joyStartPressed) {
        gPPressed = FALSE;
    }

    if (utilMouseButtons[GLFW_MOUSE_BUTTON_RIGHT] && !gClicked) {
        gShowCursor = !gShowCursor;
        utilSetCursorVisible(gShowCursor);
        gClicked = TRUE;
    } else if (!utilMouseButtons[GLFW_MOUSE_BUTTON_RIGHT]) {
        gClicked = FALSE;
    }

    // defaults (in case not moving)
    float dx = 0.0;
    float dy = 0.0;
    float da = 0.0;

    if (!gPaused) {
        if (joystick->available) {
            utilSetDeadZoneX(JOYSTICK, JOY_AXIS_L, JOY_DEAD_ZONE);
            utilSetDeadZoneY(JOYSTICK, JOY_AXIS_L, JOY_DEAD_ZONE);
            utilSetDeadZoneX(JOYSTICK, JOY_AXIS_R, JOY_DEAD_ZONE);
            utilSetDeadZoneY(JOYSTICK, JOY_AXIS_R, JOY_DEAD_ZONE);

            float axisX = utilGetAxisX(JOYSTICK, JOY_AXIS_L);
            float axisY = utilGetAxisY(JOYSTICK, JOY_AXIS_L);
            float axisA = utilGetAxisX(JOYSTICK, JOY_AXIS_R);

            // move left/right (left x-axis)
            dx = WASD_SPEED * axisX;
            // move up/down (left y-axis)
            dy = WASD_SPEED * axisY;
            // rotate (right x-axis)
            da = ROTATE_SPEED * axisA;
        } else {
            if (utilKeys[GLFW_KEY_LEFT]) {
                dx = -WASD_SPEED;
            } else if (utilKeys[GLFW_KEY_RIGHT]) {
                dx = +WASD_SPEED;
            }

            if (utilKeys[GLFW_KEY_UP]) {
                dy = -WASD_SPEED;
            } else if (utilKeys[GLFW_KEY_DOWN]) {
                dy = +WASD_SPEED;
            }

            if (utilKeys[GLFW_KEY_A]) {
                da = -ROTATE_SPEED;
            } else if (utilKeys[GLFW_KEY_D]) {
                da = +ROTATE_SPEED;
            }
        }
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
#define CURSOR_WIDTH   20
#define CURSOR_HEIGHT  20
void render(void * ptr) {
    struct Player * player = (struct Player *) ptr;

    utilClearScreen();
    drawPlayer(player);

    // draw a point on the player's center
    utilSetColor(0xff0000);
    utilFillPoint(player->position);

    // write some text
    struct Point2f textCursor = {1, 400};
    utilSetGlyphCursorPt(&textCursor);
    utilSetColor(0xffaa00);
    utilDrawText("The quick brown fox jumps\nover the lazy dog\n");
    utilDrawText("0123456789");

    // if paused, then write "PAUSED"
    if (gPaused) {
        utilDrawText("\n");
        utilSetColor(0xff0000);
        utilDrawText("PAUSED");
    }

    struct Joystick * joystick = &utilJoysticks[JOYSTICK];
    if (joystick->available) {
        utilDrawText("\n");
        utilSetColor(0x00aaff);

        uint numPrinted = 0;
        for (uint b = 0; b < joystick->numButtons; b++) {
            if (!joystick->buttons[b]) {
                continue;
            }

            if ((numPrinted + 1) % 10 == 0) {
                utilDrawText("\n");
            }
            char text3[4];
            if (b < 10) {
                text3[0] = 'A' + b;
                text3[1] = ' ';
                text3[2] = '\0';
            } else {
                text3[0] = 'A' + (b % 10);
                text3[1] = 'A' + (b / 10);
                text3[2] = ' ';
                text3[3] = '\0';
            }

            utilDrawText(text3);
            numPrinted++;
        }
    }
    
    // draw a cursor (crosshairs)
    struct Point2f crossHairs[2][2] = {
        {{utilMouse.x + 0, utilMouse.y - CURSOR_HEIGHT},
         {utilMouse.x + 0, utilMouse.y + CURSOR_HEIGHT}},
        {{utilMouse.x - CURSOR_WIDTH, utilMouse.y + 0},
         {utilMouse.x + CURSOR_WIDTH, utilMouse.y + 0}},
    };

    utilSetColor(0x00aaff);
    utilStrokeLine(crossHairs[0]);
    utilStrokeLine(crossHairs[1]);
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
