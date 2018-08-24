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
#include <stdio.h>

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

    // set defaults for glyphs
    utilSetGlyphDims(1, 1, 1);

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
        struct Point2f * pt  = path->vertices + p;
        struct Point2f * ctr = path->center;
        glVertex2f(pt->x + ctr->x, pt->y + ctr->y);
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
#define POINT_RADIUS 2
void utilFillPoint(const struct Point2f * point) {
    float x1 = point->x - POINT_RADIUS;
    float y1 = point->y - POINT_RADIUS;
    float x2 = point->x + POINT_RADIUS;
    float y2 = point->y + POINT_RADIUS;

    // draw a rectangle
    glBegin(GL_POLYGON); {
        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glVertex2f(x2, y1);
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
void utilRotatePoint(struct Point2f * point, float degrees) {
    float xp = point->x;
    float yp = point->y;

    float rad  = __utilDegToRad__(degrees);
    float cosA = cos(rad);
    float sinA = sin(rad);

    point->x = xp * cosA - yp * sinA;
    point->y = xp * sinA + yp * cosA;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilTranslatePolygon(struct Path2f * polygon, float dx, float dy) {
    polygon->center->x += dx;
    polygon->center->y += dy;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilRotatePolygonAboutCenter(struct Path2f * polygon, float degrees) {
    for (uint p = 0; p < polygon->length; p++) {
        utilRotatePoint(polygon->vertices + p, degrees);
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphDims(uint marginX, uint marginY, uint scaling) {
    __utilGlyphMarginX__ = marginX;
    __utilGlyphMarginY__ = marginY;
    __utilGlyphScaling__ = scaling;
}

/****************************************************************************
 * 
 ****************************************************************************/
const uint __UTIL_GLYPH_A__[][2] = {
    // vert
    {0, 0}, {0, 4},
    {2, 0}, {2, 4},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_B__[][2] = {
    // vert
    {0, 0}, {0, 4},
    {2, 0}, {2, 1},
    {2, 3}, {2, 4},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {1, 2},
    {0, 4}, {2, 4},
    // diag
    {1, 2}, {2, 1},
    {1, 2}, {2, 3},
};
const uint __UTIL_GLYPH_C__[][2] = {
    // vert
    {0, 0}, {0, 4},
    // horiz
    {0, 0}, {2, 0},
    {0, 4}, {2, 4},
};
const uint __UTIL_GLYPH_D__[][2] = {

};
const uint __UTIL_GLYPH_E__[][2] = {

};
const uint __UTIL_GLYPH_F__[][2] = {

};
const uint __UTIL_GLYPH_G__[][2] = {

};
const uint __UTIL_GLYPH_H__[][2] = {

};
const uint __UTIL_GLYPH_I__[][2] = {

};
const uint __UTIL_GLYPH_J__[][2] = {

};
const uint __UTIL_GLYPH_K__[][2] = {

};
const uint __UTIL_GLYPH_L__[][2] = {

};
const uint __UTIL_GLYPH_M__[][2] = {

};
const uint __UTIL_GLYPH_N__[][2] = {

};
const uint __UTIL_GLYPH_O__[][2] = {

};
const uint __UTIL_GLYPH_P__[][2] = {

};
const uint __UTIL_GLYPH_Q__[][2] = {

};
const uint __UTIL_GLYPH_R__[][2] = {

};
const uint __UTIL_GLYPH_S__[][2] = {

};
const uint __UTIL_GLYPH_T__[][2] = {

};
const uint __UTIL_GLYPH_U__[][2] = {

};
const uint __UTIL_GLYPH_V__[][2] = {

};
const uint __UTIL_GLYPH_W__[][2] = {

};
const uint __UTIL_GLYPH_X__[][2] = {

};
const uint __UTIL_GLYPH_Y__[][2] = {

};
const uint __UTIL_GLYPH_Z__[][2] = {

};

/****************************************************************************
 * 
 ****************************************************************************/
void __utilDrawGlyph__(const uint ** glyph, uint numVertices, uint x, uint y) {
    if (!glyph) {
        return;
    }

    if (numVertices % 2 != 0) {
        numVertices -= 1;
    }
    
    glBegin(GL_LINES); {
        for (uint v = 0; v < numVertices; v += 2) {
            uint * vertex1 = (uint *) &glyph[v];     // (uint *) glyph + (v * 2)
            uint * vertex2 = (uint *) &glyph[v + 1]; // (uint *) glyph + (v * 2) + 2

            uint v1x = vertex1[X] * __utilGlyphScaling__;
            uint v1y = vertex1[Y] * __utilGlyphScaling__;
            uint v2x = vertex2[X] * __utilGlyphScaling__;
            uint v2y = vertex2[Y] * __utilGlyphScaling__;

            glVertex2i(v1x + x, v1y + y);
            glVertex2i(v2x + x, v2y + y);
        }
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilDrawText(const char * text, struct Point2f * center) {
    uint x = center->x;
    uint y = center->y;
    for (const char * c = text; *c; c++) {
        switch (*c) {
            case 'A':
            case 'a':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_A__, 8, x, y);
                break;
            
            case 'B':
            case 'b':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_B__, 16, x, y);
                break;

            case 'C':
            case 'c':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_C__, 6, x, y);
                break;
            
            default:
                continue;
        }

        x += (__UTIL_GLYPH_WIDTH__ + __utilGlyphMarginX__) * __utilGlyphScaling__;
    }
}