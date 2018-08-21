/****************************************************************************
 * 
 ****************************************************************************/
#ifdef __APPLE__
#define LIBGL <OpenGL/gl.h>
#endif // __apple__
#ifdef __linux__
#define LIBGL <GL/gl.h>
#endif // __linux__
#include LIBGL

/****************************************************************************
 * 
 ****************************************************************************/
#include "utiltypes.h"
#include "utildraw.h"
#include "utilinit.h"
#include "utildebug.h"

/****************************************************************************
 * 
 ****************************************************************************/
void utilInit2DRenderer(void) {
    // this sets the canvas coordinates
    // args: left, right, bottom, top, near, far
	glOrtho(0, utilWinWidth, utilWinHeight, 0, 0, 1);

    // set clear color
    struct ColorRGB rgb = utilParseColor(utilBGColor);
    glClearColor(rgb.r, rgb.g, rgb.b, 0);
}

/****************************************************************************
 * 
 ****************************************************************************/
struct ColorRGB utilParseColor(uint color) {
    struct ColorRGB rgb;

    rgb.r = ((color >> 16) & 0xff) / 255.0;
    rgb.g = ((color >>  8) & 0xff) / 255.0;
    rgb.b = ( color        & 0xff) / 255.0;
    
    return rgb;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetColor(uint color) {
    struct ColorRGB rgb = utilParseColor(color);

    glColor3f(rgb.r, rgb.g, rgb.b);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilClearScreen(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilIterateVertices__(const struct Path2f * path) {
    for (uint p = 0; p < path->length; p++) {
        struct Point2f pt = path->points[p];
        glVertex2f(pt.x, pt.y);
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilStrokePolyline2D(const struct Path2f * path) {
    glBegin(GL_LINE_STRIP); {
        __utilIterateVertices__(path);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilStrokePolygon2D(const struct Path2f * path) {
    glBegin(GL_LINE_LOOP); {
        __utilIterateVertices__(path);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilFillPolygon2D(const struct Path2f * path) {
    glBegin(GL_POLYGON); {
        __utilIterateVertices__(path);
    } glEnd();
}