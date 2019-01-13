/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#include "rippleApp.h"
#include "../utils/matrix.h"
#include "../utils/gameCommon.h"

/* Rendering data */
renderData data = {0};
/* Vertices stored */
verticeInfo vertices[RIPPLE_APP_MAX_VERTICES] = {0};
/* Vertex indices */
GLushort vertexIndices[RIPPLE_APP_MAX_VERTICES] = {0};
/* Fragments to be drawn */
fragmentInfo fragments[RIPPLE_APP_MAX_FRAGMENTS] = {0};
/* Ripple Objects */
rippleObjs objs[RIPPLE_MAX_OBJECTS] = {0u};

static void rippleObjInit(GLubyte shape, float x, float y);
static void rippleObjUpdate(void);
static void rippleClearRenderData();
static void rippleObjRender(void);

/* Initialize a new ripple object with the given shape, co-ordinates and
 * with random radius, step size and thickness */
static void rippleObjInit(GLubyte shape, float x, float y) {
    for(int i = 0; i < RIPPLE_MAX_OBJECTS; i++) {
        if(objs[i].valid == GL_FALSE) {
            objs[i].valid = GL_TRUE;
            objs[i].currStep = 0u;
            objs[i].x = x;
            objs[i].y = y;
            objs[i].shape = shape;
            /* Set only dark colors */
            objs[i].color = (GLuint) (rand() & 0x7f7f7f7f);
            /* Set various different radius for each shape */
            objs[i].baseRadius = (0.005f + (0.001f * (float)(rand() % RIPPLE_MAX_WAVES)));
            /* Set the step radius as a percentage of base radius */
            objs[i].stepRadius = (objs[i].baseRadius * 0.72f);
            /* Set the base thickness as a percentage of base radius */
            objs[i].baseThickness = (objs[i].baseRadius * 0.03f);

            LOGD("Insert %d at %f %f of color: %x with bR: %f, sR: %f, bT: %f",
                 shape, x, y, objs[i].color, objs[i].baseRadius, objs[i].stepRadius,
                 objs[i].baseThickness);
            break;
        }
    }
}

/* Update the current valid objects for every step and remove any
 * ripple objects which have completed the entire cycle i.e. crossed
 * the step limit */
static void rippleObjUpdate() {
    for(int i = 0; i < RIPPLE_MAX_OBJECTS; i++) {
        if (objs[i].valid == GL_TRUE) {
            objs[i].currStep++;
            if(objs[i].currStep >= RIPPLE_MAX_STEPS) {
                objs[i].valid = GL_FALSE;
            }
        }
    }
}

/* Clear the current render data i.e. vertices and fragment data */
static void rippleClearRenderData() {
    data.fragments = &fragments[0];
    data.vertexIndices = &vertexIndices[0];
    data.vertices = &vertices[0];
    data.currVertexIdx = 0;
    data.maxVertices = RIPPLE_APP_MAX_VERTICES;
    data.maxFragments = RIPPLE_APP_MAX_FRAGMENTS;
    std::memset(&fragments[0], 0, (sizeof(fragmentInfo) * RIPPLE_APP_MAX_FRAGMENTS));
    std::memset(&vertexIndices[0], 0, (sizeof(GLushort) * RIPPLE_APP_MAX_VERTICES));
    std::memset(&vertices[0], 0, (sizeof(verticeInfo) * RIPPLE_APP_MAX_VERTICES));
}

/* Render the current state of the ripple objects */
static void rippleObjRender() {
    shapeInfo shape = {0};

    /* Clear the current render data */
    rippleClearRenderData();

    /* For every object */
    for(int i = 0; i < RIPPLE_MAX_OBJECTS; i++) {
        /* that is valid */
        if (objs[i].valid == GL_TRUE) {
            /* Calculate the offset from where the waves to be drawn
             * Initially all the waves start from the origin and after
             * sometime the waves from the origin starts to disappear
             * and only the existing waves still grow */
            int offset = ((objs[i].currStep < RIPPLE_MAX_WAVES)?(0):(objs[i].currStep - RIPPLE_MAX_WAVES));
            /* Calculate the number of waves to be drawn
             * Initially the number of waves start from 0 and increase
             * and after sometime the waves are constant and the further
             * decrease in wave count is handled by the offset above */
            int numWaves = ((objs[i].currStep < RIPPLE_MAX_WAVES)?(objs[i].currStep):(RIPPLE_MAX_WAVES));

            /* For the current waves that are valid i.e. from the current offset
             * to the current number of waves calculated */
            for(int j = offset; j < numWaves; j++) {
                /* Calculate an exponential delta for every step */
                float delta  = ((powf(100.0f, ((float)(j + 1u) / (float)RIPPLE_MAX_WAVES)) - 1.0f) / (99.0f));

                /* Calculate the radius of the currnt wave from base & step radius and the current step of a animation */
                shape.radius = (objs[i].baseRadius + (objs[i].currStep * (delta * objs[i].stepRadius)));

                /* Calculate the thickness based on the base thickness and the current step in animation */
                shape.thickness = objs[i].baseThickness + (objs[i].currStep * (delta * objs[i].baseThickness));

                /* Set color */
                shape.color  = objs[i].color;

                /* Based on the current shape draw the shape (i.e. create vertices and fragments */
                switch (objs[i].shape) {
                    case 0:
                        drawThickCircle(&data, objs[i].x, objs[i].y, 0.0f, shape);
                        break;
                    case 1:
                        drawThickPentagon(&data, objs[i].x, objs[i].y, 0.0f, shape);
                        break;
                    case 2:
                        drawThickHexagon(&data, objs[i].x, objs[i].y, 0.0f, shape);
                        break;
                    case 3:
                        drawThickDiamond(&data, objs[i].x, objs[i].y, 0.0f, shape);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

/* When the screen has to be re-drawn */
void rippleOnDraw(void) {
    /* Render the objects as in the list */
    rippleObjRender();

    /* Load the vertex data and enable the attribute */
    glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, sizeof(verticeInfo), &vertices[0].position[0] );
    glEnableVertexAttribArray ( 0 );
    /* Load vertex normals and enable the attribute  */
    glVertexAttrib3f(1, 0.0f, 0.0f, 1.0f);
    glEnableVertexAttribArray ( 1 );
    /* Load the vertex data and enable the attribute */
    glVertexAttribPointer ( 2, 4, GL_FLOAT, GL_FALSE, sizeof(verticeInfo), &vertices[0].color[0] );
    glEnableVertexAttribArray ( 2 );

    /* For every fragments */
    for (int i = 0; i < RIPPLE_APP_MAX_FRAGMENTS; ++i) {
        /* that are valid */
        if(fragments[i].valid == GL_TRUE) {
            /* draw them */
            glDrawElements(fragments[i].drawMode, fragments[i].numVertices, GL_UNSIGNED_SHORT,
                           &vertexIndices[fragments[i].startVertexIdx]);
        }
    }
}

/* For every touch input */
void rippleOnTouch (float fPosX, float fPosY) {
    static uint32 lastClickTS = 0u;
    int r = (rand() % 4u);

    /* Debounce the touch to avoid creating multiple
     * objects in one place */
    if(currTimeDiff(lastClickTS) > 240u) {
        /* Create a new objects at the location */
        rippleObjInit((GLubyte)r, fPosX, fPosY);
        /* Save time for last touch for de-bouncing */
        lastClickTS = currTimeMS();
    }
}

/* For every timer tick */
void rippleTimerTask() {
    /* Update the current objects status */
    rippleObjUpdate();
}

/* When app is initialized */
void rippleOnInit() {
    /* Clear the render data */
    rippleClearRenderData();
    /* Clear the object data */
    std::memset(&objs[0], 0, (sizeof(rippleObjs) * RIPPLE_MAX_OBJECTS));
}


