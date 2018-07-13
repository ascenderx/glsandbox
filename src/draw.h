#ifndef DRAW_H
#define DRAW_H

#ifndef uint
typedef unsigned int uint;
#endif // uint

struct Point2f {
   float x;
   float y;
};

struct Path2f {
   uint length;
   struct Point2f * points;
};

void uInitEngine(void);
void uUpdate(void);
void uInit2DRenderer(uint width, uint height);
void uSetColor(uint color);
void uPolyline2D(const struct Path2f * path);
void uRender2D(void);

#endif // DRAW_H
