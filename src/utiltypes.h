#ifndef UTIL_TYPES_H
#define UTIL_TYPES_H

/****************************************************************************
 * 
 ****************************************************************************/
#include <GLFW/glfw3.h>

/****************************************************************************
 * 
 ****************************************************************************/
#ifndef uint
typedef unsigned int uint;
#endif // uint

/****************************************************************************
 * 
 ****************************************************************************/
#ifndef bool
typedef char boolean;
#define FALSE 0
#define TRUE  1
#else
typedef bool boolean;
#define FALSE false
#define TRUE  true
#endif // bool

/****************************************************************************
 * 
 ****************************************************************************/
#define STRING_MAX_LENGTH 256

/****************************************************************************
 * 
 ****************************************************************************/
struct UtilitySettings {
    uint  winWidth;
    uint  winHeight;
    char  winTitle[STRING_MAX_LENGTH];
    uint  framerate;
    uint  bgColor;
    void (* init)(void);
    void (* input)(void);
    void (* update)(void);
    void (* render)(void);
    GLFWwindow * window;
};

#endif // UTIL_TYPES_H