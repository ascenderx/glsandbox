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
        utilKeys[ukey]++;
    } else if (action == GLFW_RELEASE) {
        utilKeys[ukey] = 0;
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilIsKeyDown(uint key) {
    if (key >= __UTIL_MAX_KEYS__) {
        return FALSE;
    }

    uint state = utilKeys[key];
    return (state >= 1);
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilMouseFunc__(GLFWwindow * window, double xpos, double ypos) {
    utilMouse.x = (float) xpos;
    utilMouse.y = (float) ypos;
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilShowHideCursor__(boolean visible) {
    if (!__utilWindow__) {
        return;
    }

    int mode = (visible) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN;
    glfwSetInputMode(__utilWindow__, GLFW_CURSOR, mode);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetCursorVisible(boolean visible) {
    __utilCursorVisible__ = visible;
    __utilShowHideCursor__(visible);
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilMouseButtonFunc__(GLFWwindow * window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        utilMouseButtons[button]++;
    } else if (action == GLFW_RELEASE) {
        utilMouseButtons[button] = 0;
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilJoyConnectFunc__(int joy, int event) {
    if (event == GLFW_CONNECTED) {
        utilJoysticks[joy] = TRUE;
    } else {
        utilJoysticks[joy] = FALSE;
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
float __utilGetAxis__(uint joy, uint stick, boolean xory) {
    if (!glfwJoystickPresent(joy)) {
        return 0.0;
    }

    int numAxes;
    const float * axes = glfwGetJoystickAxes(joy, &numAxes);
    if (!numAxes || !axes) {
        return 0.0;
    }

    uint axis = stick * 2 + xory;
    if (axis >= numAxes) {
        return 0.0;
    }

    return axes[axis];
}

/****************************************************************************
 * 
 ****************************************************************************/
float utilGetAxisX(uint joy, uint stick) {
    return __utilGetAxis__(joy, stick, UTIL_AXIS_X);
}

/****************************************************************************
 * 
 ****************************************************************************/
float utilGetAxisY(uint joy, uint stick) {
    return __utilGetAxis__(joy, stick, UTIL_AXIS_Y);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilInitInputHandlers() {
    if (!__utilWindow__) {
        return;
    }

    for (uint k = 0; k < __UTIL_MAX_KEYS__; k++) {
        utilKeys[k] = 0;
    }

    for (uint j = 0; j < GLFW_JOYSTICK_LAST; j++) {
        if (glfwJoystickPresent(j)) {
            __utilJoyConnectFunc__(j, GLFW_CONNECTED);
        }
    }

    glfwSetKeyCallback(__utilWindow__, __utilKeyFunc__);

    utilMouse.x = 0;
    utilMouse.y = 0;
    glfwSetCursorPosCallback(__utilWindow__, __utilMouseFunc__);
    __utilShowHideCursor__(__utilCursorVisible__);
    
    for (uint b = 0; b < GLFW_MOUSE_BUTTON_LAST; b++) {
        utilMouseButtons[b] = 0;
    }
    
    glfwSetMouseButtonCallback(__utilWindow__, __utilMouseButtonFunc__);
    
#if GLFW_VERSION_MINOR >= 2
    glfwSetJoystickCallback(__utilJoyConnectFunc__);
#endif // GLFW_VERSION_MINOR
}
