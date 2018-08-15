#include <string.h>

#include "utiltypes.h"
#include "utilinit.h"
#include "utildraw.h"
#include "utilinput.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void init(void);
void input(void);
void update(void);
void render(void);

int main(int argc, char ** argv) {
    struct UtilitySettings stgs;
    stgs.winWidth  = 400;
    stgs.winHeight = 400;
    strncpy(stgs.winTitle, "GLSandbox #1", STRING_MAX_LENGTH);
    stgs.framerate = 30;
    stgs.bgColor   = 0x000000;
    stgs.init      = init;
    stgs.input     = input;
    stgs.update    = update;
    stgs.render    = render;

    return EXIT_SUCCESS;
}

void init(void) {

}

void input(void) {

}

void update(void) {

}

void render(void) {
    
}