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
    utilInitialized = FALSE;

    if (glfwInit()) {
        // initialize defaults
        utilWinWidth    = 640;
        utilWinHeight   = 480;
        utilWinTitle    = "GLSandbox";
        utilFramerate   = 60;
        utilBGColor     = 0x000000;
        utilUserData    = NULL;
        utilUserInput   = NULL;
        utilUserUpdate  = NULL;
        utilUserRender  = NULL;
        utilUserCleanUp = NULL;
        utilInitialized = TRUE;
    }

    return utilInitialized;
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilMainLoop(void) {
    if (!utilUserInput || !utilUserUpdate || !utilUserRender) {
        return FALSE;
    }

    utilWindow = glfwCreateWindow(utilWinWidth, utilWinHeight, utilWinTitle, NULL, NULL);
    if (!utilWindow) {
        glfwTerminate();
        return FALSE;
    }

    glfwMakeContextCurrent(utilWindow);

    utilInit2DRenderer();

    while (!glfwWindowShouldClose(utilWindow)) {
        glfwPollEvents();

        // run user functions
        utilUserInput(utilUserData);
        utilUserUpdate(utilUserData);
        utilUserRender(utilUserData);

        glfwSwapBuffers(utilWindow);

        usleep(1000000 / utilFramerate);
    }

    glfwTerminate();

    if (utilUserCleanUp) {
        utilUserCleanUp(utilUserData);
    }

    return TRUE;
}
