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
uint         __utilWinWidth__;
uint         __utilWinHeight__;
char *       __utilWinTitle__;
uint         __utilFramerate__;
uint         __utilBGColor__;
void *       __utilUserData__;
boolean      __utilInitialized__;
GLFWwindow * __utilWindow__;
boolean      __utilRunning__;
void (* __utilTickFunc__)(void *);

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilInitEngine();
void    utilSetWinDims(const uint width, const uint height);
void    utilSetWinTitle(char * title);
void    utilSetFramerate(const uint framerate);
void    utilSetBGColor(const uint color);
void    utilSetUserData(void * pointer);
void    utilSetTickFunc(void (func(void *)));
boolean utilMainLoop(void);
void    utilEnd(void);

#endif // UTIL_INIT_H
