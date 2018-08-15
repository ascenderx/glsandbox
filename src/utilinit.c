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
boolean utilInitEngine(struct UtilitySettings * stgs) {
    if (!glfwInit()) {
        return FALSE;
    }
    
    stgs->window = glfwCreateWindow(stgs->winWidth, stgs->winHeight, stgs->winTitle, NULL, NULL);
    if (!stgs->window) {
        glfwTerminate();
        return FALSE;
    }

    glfwMakeContextCurrent(stgs->window);

    // init user data
    if (stgs->init) {
        stgs->init();
    }

    return TRUE;
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilMainLoop(struct UtilitySettings * stgs) {
    if (!stgs->input || !stgs->update || !stgs->render) {
        return FALSE;
    }

    while (!glfwWindowShouldClose(stgs->window)) {
        glfwPollEvents();

        // run user functions
        stgs->input();
        stgs->update();
        stgs->render();

        glfwSwapBuffers(stgs->window);

        usleep(1000000 / stgs->framerate);
    }

    glfwTerminate();

    return TRUE;
}
