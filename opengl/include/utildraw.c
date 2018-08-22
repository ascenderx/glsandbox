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
#include <math.h>

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
void utilInitRenderer(uint width, uint height, uint color) {
    // this sets the canvas coordinates
    // args: left, right, bottom, top, near, far
	glOrtho(0, width, height, 0, 0, 1);

    // set clear color
    struct ColorRGB rgb = utilParseColor(color);
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
        struct Point2f pt  = path->points[p];
        struct Point2f ctr = path->center;
        glVertex2f(pt.x + ctr.x, pt.y + ctr.y);
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilStrokePolyline(const struct Path2f * path) {
    glBegin(GL_LINE_STRIP); {
        __utilIterateVertices__(path);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilStrokePolygon(const struct Path2f * path) {
    glBegin(GL_LINE_LOOP); {
        __utilIterateVertices__(path);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilFillPolygon(const struct Path2f * path) {
    glBegin(GL_POLYGON); {
        __utilIterateVertices__(path);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
float __utilDegToRad__(float degrees) {
    return (degrees * PI) / 180.0;
}

/****************************************************************************
 * 
 ****************************************************************************/
float __utilRadToDeg__(float radians) {
    return (radians * 180.0) / PI;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilRotatePoint(struct Point2f * point, const struct Point2f * center, float degrees) {
    float xp = point->x;
    float yp = point->y;
    float xc = center->x;
    float yc = center->y;

    float rad  = __utilDegToRad__(degrees);
    float cosA = cos(rad);
    float sinA = sin(rad);

    point->x = xp * cosA - yp * sinA + xc;
    point->y = xp * sinA + yp * cosA + yc;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilTranslatePolygon(struct Path2f * polygon, float dx, float dy) {
    polygon->center.x += dx;
    polygon->center.y += dy;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilRotatePolygonAboutCenter(struct Path2f * polygon, float degrees) {
    for (uint p = 0; p < polygon->length; p++) {
        utilRotatePoint(&polygon->points[p], &polygon->center, degrees);
    }
}