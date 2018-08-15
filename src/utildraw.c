#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif // __apple__

#ifdef __linux__
#include <GL/gl.h>
#endif // __linux__

#include "utiltypes.h"
#include "utildraw.h"

void utilInit2DRenderer(struct UtilitySettings * stgs) {
    // this sets the canvas coordinates
    // args: left, right, bottom, top, near, far
	glOrtho(0, stgs->winWidth, stgs->winHeight, 0, 0, 1);

    // set clear color
    struct ColorRGB rgb = utilParseColor(stgs->bgColor);
    glClearColor(rgb.r, rgb.g, rgb.b, 0);
}

struct ColorRGB utilParseColor(uint color) {
    struct ColorRGB rgb;

    rgb.r = ((color >> 16) & 0xff) / 255.0;
    rgb.g = ((color >>  8) & 0xff) / 255.0;
    rgb.b = ( color        & 0xff) / 255.0;
    
    return rgb;
}

void utilSetColor(uint color) {
    struct ColorRGB rgb = utilParseColor(color);

    glColor3f(rgb.r, rgb.g, rgb.b);
}

void utilClearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void utilPolyline2D(const struct Path2f * path) {
    glBegin(GL_LINE_STRIP); {
        for (uint p = 0; p < path->length; p++) {
            struct Point2f pt = path->points[p];
            glVertex2f(pt.x, pt.y);
        }
    } glEnd();
}