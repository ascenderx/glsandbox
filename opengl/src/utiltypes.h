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

#endif // UTIL_TYPES_H