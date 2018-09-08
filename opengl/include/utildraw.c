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
    utilSetGlyphCursorXY(0, 0);
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
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_B__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
    // diag
    {1, 1}, {2, 0},
};
const uint __UTIL_GLYPH_C__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_D__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {1, 2},
    // diag
    {1, 2}, {2, 1},
};
const uint __UTIL_GLYPH_E__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {1, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_F__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {1, 1},
};
const uint __UTIL_GLYPH_G__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {1, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_H__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_I__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_J__[][2] = {
    // vert
    {0, 1}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_K__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // diag
    {0, 1}, {2, 0},
    {0, 1}, {2, 2},
};
const uint __UTIL_GLYPH_L__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // horiz
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_M__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // diag
    {0, 0}, {1, 2},
    {1, 2}, {2, 0},
};
const uint __UTIL_GLYPH_N__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // diag
    {0, 0}, {2, 2},
};
const uint __UTIL_GLYPH_O__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_P__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_Q__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {1, 2},
    // diag
    {1, 1}, {2, 2},
    {1, 2}, {2, 1},
};
const uint __UTIL_GLYPH_R__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    // diag
    {1, 1}, {2, 2},
};
const uint __UTIL_GLYPH_S__[][2] = {
    // vert
    {0, 0}, {0, 1},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_T__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 0}, {2, 0},
};
const uint __UTIL_GLYPH_U__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_V__[][2] = {
    // diag
    {0, 0}, {1, 2},
    {1, 2}, {2, 0},
};
const uint __UTIL_GLYPH_W__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // diag
    {0, 2}, {1, 1},
    {1, 1}, {2, 2},
};
const uint __UTIL_GLYPH_X__[][2] = {
    // diag
    {0, 0}, {2, 2},
    {0, 2}, {2, 0},
};
const uint __UTIL_GLYPH_Y__[][2] = {
    // vert
    {1, 1}, {1, 2},
    // diag
    {0, 0}, {1, 1},
    {1, 1}, {2, 0},
};
const uint __UTIL_GLYPH_Z__[][2] = {
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
    // diag
    {0, 2}, {2, 0},
};

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphCursorXY(float x, float y) {
    __utilGlyphCursorCurrent__.x = x;
    __utilGlyphCursorCurrent__.y = y;
    __utilGlyphCursorStart__.x   = x;
    __utilGlyphCursorStart__.y   = y;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphCursorPt(struct Point2f * pt) {
    utilSetGlyphCursorXY(pt->x, pt->y);
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilAdvanceGlyphCursorX__(int numChars) {
    uint w = __UTIL_GLYPH_WIDTH__ * __utilGlyphScaling__;
    uint m = __utilGlyphMarginX__ - 1;
    __utilGlyphCursorCurrent__.x += (w + m) * numChars;
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilAdvanceGlyphCursorY__(int numLines) {
    __utilGlyphCursorCurrent__.x = __utilGlyphCursorStart__.x;
    
    uint h = __UTIL_GLYPH_HEIGHT__ * __utilGlyphScaling__;
    uint m = __utilGlyphMarginY__ - 1;
    __utilGlyphCursorCurrent__.y += (h + m) * numLines;
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilDrawGlyph__(const uint ** glyph, uint numLines) {
    if (!glyph || numLines == 0) {
        return;
    }

    uint numVertices = numLines * 2;
    float x = __utilGlyphCursorCurrent__.x;
    float y = __utilGlyphCursorCurrent__.y;
        
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
    
    __utilAdvanceGlyphCursorX__(1);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilDrawText(const char * text) {
    for (const char * c = text; *c; c++) {
        switch (*c) {
            case 'A':
            case 'a':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_A__, 4);
                break;
            
            case 'B':
            case 'b':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_B__, 8);
                break;

            case 'C':
            case 'c':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_C__, 3);
                break;
            
            case 'D':
            case 'd':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_D__, 5);
                break;
                
            case 'E':
            case 'e':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_E__, 4);
                break;
                
            case 'F':
            case 'f':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_F__, 3);
                break;
            
            case 'G':
            case 'g':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_G__, 5);
                break;
            
            case 'H':
            case 'h':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_H__, 3);
                break;
            
            case 'I':
            case 'i':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_I__, 3);
                break;
            
            case 'J':
            case 'j':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_J__, 3);
                break;
            
            case 'K':
            case 'k':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_K__, 3);
                break;
            
            case 'L':
            case 'l':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_L__, 2);
                break;
            
            case 'M':
            case 'm':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_M__, 4);
                break;
            
            case 'N':
            case 'n':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_N__, 3);
                break;
            
            case 'O':
            case 'o':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_O__, 4);
                break;
            
            case 'P':
            case 'p':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_P__, 4);
                break;
            
            case 'Q':
            case 'q':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_Q__, 6);
                break;
            
            case 'R':
            case 'r':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_R__, 5);
                break;
            
            case 'S':
            case 's':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_S__, 5);
                break;
            
            case 'T':
            case 't':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_T__, 2);
                break;
            
            case 'U':
            case 'u':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_U__, 3);
                break;
            
            case 'V':
            case 'v':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_V__, 2);
                break;
            
            case 'W':
            case 'w':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_W__, 4);
                break;
            
            case 'X':
            case 'x':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_X__, 2);
                break;
            
            case 'Y':
            case 'y':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_Y__, 3);
                break;
            
            case 'Z':
            case 'z':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_Z__, 4);
                break;
            
            case '\n':
                __utilAdvanceGlyphCursorY__(1);
                continue;
            
            case ' ':
                __utilAdvanceGlyphCursorX__(1);
                break;
            
            default:
                continue;
        }
    }
}
