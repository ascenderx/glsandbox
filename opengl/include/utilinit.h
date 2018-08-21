#ifndef UTIL_INIT_H
#define UTIL_INIT_H

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
uint         utilWinWidth;
uint         utilWinHeight;
char *       utilWinTitle;
uint         utilFramerate;
uint         utilBGColor;
void *       utilUserData;
boolean      utilInitialized;
GLFWwindow * utilWindow;
void (* utilUserInput)(void *);
void (* utilUserUpdate)(void *);
void (* utilUserRender)(void *);
void (* utilUserCleanUp)(void *);

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilInitEngine();
boolean utilMainLoop(void);

#endif // UTIL_INIT_H