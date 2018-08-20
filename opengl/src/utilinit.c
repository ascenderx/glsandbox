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

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilInitEngine(uint winWidth, uint winHeight, char * winTitle) {
    utilInitialized = FALSE;

    if (glfwInit()) {
        // initialize defaults
        utilWinWidth    = winWidth;
        utilWinHeight   = winHeight;
        utilWinTitle    = winTitle;
        utilFramerate   = 60;
        utilBGColor     = 0x000000;
        utilUserData    = NULL;
        utilUserInput   = NULL;
        utilUserUpdate  = NULL;
        utilUserRender  = NULL;
        utilUserCleanUp = NULL;
        utilInitialized = TRUE;
    }

    utilWindow = glfwCreateWindow(utilWinWidth, utilWinHeight, utilWinTitle, NULL, NULL);
    if (!utilWindow) {
        glfwTerminate();
        return FALSE;
    }

    glfwMakeContextCurrent(utilWindow);

    return utilInitialized;
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilMainLoop(void) {
    if (!utilUserInput || !utilUserUpdate || !utilUserRender) {
        return FALSE;
    }

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
