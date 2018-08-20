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

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilInitEngine() {
    utilInitialized = FALSE;

    if (!glfwInit()) {
        return FALSE;
    }
    
    utilWindow = glfwCreateWindow(utilWinWidth, utilWinHeight, utilWinTitle, NULL, NULL);
    if (!utilWindow) {
        glfwTerminate();
        return FALSE;
    }

    glfwMakeContextCurrent(utilWindow);

    // init user data
    if (utilUserInit) {
        utilUserInit(utilUserData);
    }

    utilInitialized = TRUE;

    return TRUE;
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilMainLoop() {
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
