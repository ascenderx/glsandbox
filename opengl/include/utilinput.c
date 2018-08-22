/****************************************************************************
 * 
 ****************************************************************************/
#include <GLFW/glfw3.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "utilinput.h"
#include "utiltypes.h"
#include "utilinit.h"

/****************************************************************************
 * 
 ****************************************************************************/
void __utilKeyFunc__(GLFWwindow * window, int key, int scancode, int action, int mods) {
    uint ukey = (uint) key;
    if (ukey >= __UTIL_MAX_KEYS__) {
        return;
    }

    if (action == GLFW_PRESS) {
        __utilKeys__[ukey]++;
    } else if (action == GLFW_RELEASE) {
        __utilKeys__[ukey] = 0;
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilIsKeyDown(uint key) {
    if (key >= __UTIL_MAX_KEYS__) {
        return FALSE;
    }

    uint state = __utilKeys__[key];
    return (state == GLFW_PRESS);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilInitInputHandlers() {
    if (!__utilWindow__) {
        return;
    }

    for (uint k = 0; k < __UTIL_MAX_KEYS__; k++) {
        __utilKeys__[k] = 0;
    }

    glfwSetKeyCallback(__utilWindow__, __utilKeyFunc__);
}