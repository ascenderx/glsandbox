#ifndef UTIL_INPUT_H
#define UTIL_INPUT_H

/****************************************************************************
 * 
 ****************************************************************************/
#include <GLFW/glfw3.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "utiltypes.h"

/****************************************************************************
 * 
 ****************************************************************************/
#define __UTIL_MAX_KEYS__ 350
uint __utilKeys__[__UTIL_MAX_KEYS__];

/****************************************************************************
 * 
 ****************************************************************************/
void __utilKeyFunc__(GLFWwindow * window, int key, int scancode, int action, int mods);

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilIsKeyDown(uint key);

/****************************************************************************
 * 
 ****************************************************************************/
struct Point2f utilMouse;

/****************************************************************************
 * 
 ****************************************************************************/
void __utilMouseFunc__(GLFWwindow * window, double xpos, double ypos);

/****************************************************************************
 * 
 ****************************************************************************/
boolean __utilCursorVisible__;
void __utilShowHideCursor__(boolean visible);

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetCursorVisible(boolean visible);

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilJoysticks[GLFW_JOYSTICK_LAST];

/****************************************************************************
 * 
 ****************************************************************************/
void __utilJoyConnectFunc__(int joy, int event);

/****************************************************************************
 * 
 ****************************************************************************/
#define UTIL_AXIS_X 0
#define UTIL_AXIS_Y 1
float __utilGetAxis__(uint joy, uint stick, boolean xory);

/****************************************************************************
 * 
 ****************************************************************************/
float utilGetAxisX(uint joy, uint stick);

/****************************************************************************
 * 
 ****************************************************************************/
float utilGetAxisY(uint joy, uint stick);

/****************************************************************************
 * 
 ****************************************************************************/
void utilInitInputHandlers(void);

#endif // UTIL_INPUT_H