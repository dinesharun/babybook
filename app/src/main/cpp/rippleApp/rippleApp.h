/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#ifndef BABYBOOK_RIPPLEAPP_H
#define BABYBOOK_RIPPLEAPP_H

#include "../utils/gameCommon.h"

#define RIPPLE_APP_MAX_VERTICES  (3000)
#define RIPPLE_APP_MAX_FRAGMENTS (1000)

#define RIPPLE_SHAPE_CIRCLE   (0)
#define RIPPLE_SHAPE_DIAMOND  (1)
#define RIPPLE_SHAPE_HEXAGON  (2)
#define RIPPLE_SHAPE_PENTAGON (3)

#define RIPPLE_MAX_OBJECTS    (100)
#define RIPPLE_MAX_WAVES      (30)
#define RIPPLE_MAX_STEPS      (RIPPLE_MAX_WAVES * 2u)

typedef struct {
    float x;
    float y;
    float baseRadius;
    float stepRadius;
    float baseThickness;
    GLuint color;
    GLushort currStep;
    GLubyte  shape;
    bool valid;
} rippleObjs;

void rippleOnDraw(void);
void rippleOnTouch (float fPosX, float fPosY);
void rippleTimerTask(void);
void rippleOnInit(void);

#endif //BABYBOOK_RIPPLEAPP_H
