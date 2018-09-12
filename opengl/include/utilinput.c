/****************************************************************************
 * 
 ****************************************************************************/
#include <stdlib.h> // *alloc, free
#include <math.h> // *abs*

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
        utilJoysticks[joy].available = TRUE;
        utilJoysticks[joy].name = (char *) glfwGetJoystickName(joy);
        
        int numButtons;
        const uchar * buttons = glfwGetJoystickButtons(joy, &numButtons);
        utilJoysticks[joy].numButtons = numButtons;
        utilJoysticks[joy].buttons = (uchar *) calloc(numButtons, sizeof(uchar));
        for (uint b = 0; b < numButtons; b++) {
            utilJoysticks[joy].buttons[b] = buttons[b];
        }

        int numAxes;
        const float * axes = glfwGetJoystickAxes(joy, &numAxes);
        utilJoysticks[joy].numAxes = numAxes;
        utilJoysticks[joy].axes = (float *) calloc(numAxes, sizeof(float));
        utilJoysticks[joy].__deadZones__ = (float *) calloc(numAxes, sizeof(float));
        for (uint a = 0; a < numAxes; a++) {
            utilJoysticks[joy].axes[a] = axes[a];
            utilJoysticks[joy].__deadZones__[a] = 0.0f;
        }
    } else {
        utilJoysticks[joy].available = FALSE;
        utilJoysticks[joy].name = "";
        utilJoysticks[joy].numButtons = 0;

        if (utilJoysticks[joy].buttons) {
            free(utilJoysticks[joy].buttons);
            utilJoysticks[joy].buttons = NULL;
        }
        if (utilJoysticks[joy].axes) {
            free(utilJoysticks[joy].axes);
            utilJoysticks[joy].axes = NULL;
        }
        if (utilJoysticks[joy].__deadZones__) {
            free(utilJoysticks[joy].__deadZones__);
            utilJoysticks[joy].__deadZones__ = NULL;
        }
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
float __utilGetAxis__(uint joy, uint stick, boolean xory) {
    if (!glfwJoystickPresent(joy)) {
        __utilJoyConnectFunc__(joy, GLFW_DISCONNECTED);
        return 0.0f;
    }

    uint axis = stick * 2 + xory;
    if (axis >= utilJoysticks[joy].numAxes) {
        return 0.0f;
    }

    float deadZone = utilJoysticks[joy].__deadZones__[axis];
    float axisAmt = utilJoysticks[joy].axes[axis];

    if (axisAmt < -deadZone || axisAmt > +deadZone) {
        return axisAmt;
    } else {
        return 0.0f;
    }
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
void __utilSetDeadZone__(uint joy, uint stick, boolean xory, float deadZone) {
    if (!glfwJoystickPresent(joy)) {
        __utilJoyConnectFunc__(joy, GLFW_DISCONNECTED);
        return;
    }

    uint axis = stick * 2 + xory;
    if (axis >= utilJoysticks[joy].numAxes) {
        return;
    }

    utilJoysticks[joy].__deadZones__[axis] = fabsf(deadZone);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetDeadZoneX(uint joy, uint stick, float deadZone) {
    __utilSetDeadZone__(joy, stick, UTIL_AXIS_X, deadZone);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetDeadZoneY(uint joy, uint stick, float deadZone) {
    __utilSetDeadZone__(joy, stick, UTIL_AXIS_Y, deadZone);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilInitInputHandlers(void) {
    if (!__utilWindow__) {
        return;
    }

    for (uint k = 0; k < __UTIL_MAX_KEYS__; k++) {
        utilKeys[k] = 0;
    }

    for (uint j = 0; j < GLFW_JOYSTICK_LAST; j++) {
        if (glfwJoystickPresent(j)) {
            utilJoysticks[j].buttons = NULL;
            utilJoysticks[j].axes = NULL;
            utilJoysticks[j].__deadZones__ = NULL;
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

#include <stdio.h>
/****************************************************************************
 * 
 ****************************************************************************/
void utilUpdateInputHandlers(void) {
#if GLFW_VERSION_MINOR >= 2
    for (uint j = 0; j < GLFW_JOYSTICK_LAST; j++) {
        if (!glfwJoystickPresent(j)) {
            continue;
        }

        if (!utilJoysticks[j].available) {
            __utilJoyConnectFunc__(j, GLFW_CONNECTED);
        }

        int numAxes;
        const float * axes = glfwGetJoystickAxes(j, &numAxes);
        for (uint a = 0; a < numAxes; a++) {
            utilJoysticks[j].axes[a] = axes[a];
        }

        int numButtons;
        const uchar * buttons = glfwGetJoystickButtons(j, &numButtons);
        for (uint b = 0; b < numButtons; b++) {
            utilJoysticks[j].buttons[b] = buttons[b];
        }
    }
#endif // GLFW_VERSION_MINOR
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilReleaseInputHandlers(void) {
    for (uint j = 0; j < GLFW_JOYSTICK_LAST; j++) {
        __utilJoyConnectFunc__(j, GLFW_DISCONNECTED);
    }
}
