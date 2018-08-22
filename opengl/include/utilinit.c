/****************************************************************************
 * 
 ****************************************************************************/
#include <unistd.h> // usleep

/****************************************************************************
 * 
 ****************************************************************************/
#include <GLFW/glfw3.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "utilinit.h"
#include "utiltypes.h"
#include "utildraw.h"

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilInitEngine() {
    __utilInitialized__ = FALSE;

    if (glfwInit()) {
        // initialize defaults
        utilSetWinDims(640, 480);
        utilSetWinTitle("GLSandbox");
        utilSetFramerate(60);
        utilSetBGColor(0x000000);
        utilSetTickFunc(NULL);
        __utilInitialized__ = TRUE;
    }

    return __utilInitialized__;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetWinDims(const uint width, const uint height) {
    __utilWinWidth__  = width;
    __utilWinHeight__ = height;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetWinTitle(char * title) {
    __utilWinTitle__ = title;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetFramerate(const uint framerate) {
    __utilFramerate__ = framerate;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetBGColor(const uint color) {
    __utilBGColor__ = color;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetUserData(void * pointer) {
    __utilUserData__ = pointer;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetTickFunc(void (func(void *))) {
    __utilTickFunc__ = func;
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilMainLoop(void) {
    __utilWindow__ = glfwCreateWindow(
        __utilWinWidth__,
        __utilWinHeight__,
        __utilWinTitle__,
        NULL,
        NULL
    );
    if (!__utilWindow__) {
        glfwTerminate();
        return FALSE;
    }

    glfwMakeContextCurrent(__utilWindow__);

    utilInit2DRenderer(__utilWinWidth__, __utilWinHeight__, __utilBGColor__);

    while (!glfwWindowShouldClose(__utilWindow__)) {
        glfwPollEvents();

        // run user function
        if (__utilTickFunc__) {
            __utilTickFunc__(__utilUserData__);
        }

        glfwSwapBuffers(__utilWindow__);

        usleep(1000000 / __utilFramerate__);
    }

    glfwTerminate();

    return TRUE;
}
