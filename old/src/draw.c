#include <stdlib.h> // calloc
#include <stdio.h>  // printf

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif // __apple__

#ifdef __linux__
#include <GL/gl.h>
#endif // __linux__

#include "draw.h"

struct Point2f pts[] = {
    {0, 0}, {100, 200}, {30, 400}
};
struct Path2f path1;

void uInitEngine() {
    path1.length = 3;
    path1.points = pts;
}

void uUpdate() {
    for (uint p = 0; p < path1.length; p++) {
        path1.points[p].y /= 1.005;
    }
}

void uInit2DRenderer(uint width, uint height) {
    // this sets the canvas coordinates
    // args: left, right, bottom, top, near, far
	glOrtho(0, width, height, 0, 0, 1);

    // set clear color
    glClearColor(0, 0, 0, 0);
}

void uSetColor(uint color) {
    float r = ((color >> 16) & 0xff) / 255.0;
    float g = ((color >>  8) & 0xff) / 255.0;
    float b = ( color        & 0xff) / 255.0;

    glColor3f(r, g, b);
}

void uPolyline2D(const struct Path2f * path) {
    glBegin(GL_LINE_STRIP); {
        for (uint p = 0; p < path->length; p++) {
            struct Point2f pt = path->points[p];
            glVertex2f(pt.x, pt.y);
        }
    } glEnd();
}

void uRender2D() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    uSetColor(0x00aaff);
    glLineWidth(4);

    uPolyline2D(&path1);
}

