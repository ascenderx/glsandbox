#ifndef UTIL_INIT_H
#define UTIL_INIT_H

#include <GLFW/glfw3.h>
#include "utiltypes.h"

#define EXIT_SUCCESS 0
#define EXIT_ERROR   1

boolean utilInitEngine(struct UtilitySettings * stgs);
boolean utilMainLoop(struct UtilitySettings * stgs);

#endif // UTIL_INIT_H