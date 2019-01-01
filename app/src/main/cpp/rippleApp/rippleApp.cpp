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
static void rippleObjRender(void);

static void rippleObjInit(GLubyte shape, float x, float y) {
    for(int i = 0; i < RIPPLE_MAX_OBJECTS; i++) {
        if(objs[i].valid == GL_FALSE) {
            objs[i].valid = GL_TRUE;
            objs[i].currStep = 0u;
            objs[i].x = x;
            objs[i].y = y;
            objs[i].shape = shape;
            objs[i].color = (GLuint) rand();
            objs[i].baseRadius = (0.003f * (float)(rand() % RIPPLE_MAX_WAVES));
            objs[i].stepRadius = (0.003f * (float)(rand() % RIPPLE_MAX_STEPS));
            break;
        }
    }
}

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

static void rippleObjRender() {
    shapeInfo shape = {0};

    rippleOnInit();

    for(int i = 0; i < RIPPLE_MAX_OBJECTS; i++) {
        if (objs[i].valid == GL_TRUE) {
            for(int j = 0; j < RIPPLE_MAX_WAVES; j++) {
                float delta  = (float)sin(((float)(j + 1u) / (float)RIPPLE_MAX_WAVES) * 2.3f * M_PI);
                shape.radius = (objs[i].baseRadius + (objs[i].currStep * delta * objs[i].stepRadius));
                shape.color  = objs[i].color;
                switch (objs[i].shape) {
                    case 0:
                        drawCircle(&data, objs[i].x, objs[i].y, 0.0f, shape);
                        break;
                    case 1:
                        drawPentagon(&data, objs[i].x, objs[i].y, 0.0f, shape);
                        break;
                    case 2:
                        drawHexagon(&data, objs[i].x, objs[i].y, 0.0f, shape);
                        break;
                    case 3:
                        drawDiamond(&data, objs[i].x, objs[i].y, 0.0f, shape);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void rippleOnDraw(void) {
    /* Draw the objects as in the list and update the ripple objects list */
    rippleObjRender();

    /* Load the vertex data and enable the attribute */
    glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, sizeof(verticeInfo), &vertices[0].position[0] );
    glEnableVertexAttribArray ( 0 );
    /* Load vertex normals and enable the attribute  */
    glVertexAttrib3f(1, 0.0f, 0.0f, 1.0f);
    glEnableVertexAttribArray ( 1 );
    /* Load the vertex data and enable the attribute */
    glVertexAttribPointer ( 2, 4, GL_BYTE, GL_FALSE, sizeof(verticeInfo), &vertices[0].color[0] );
    glEnableVertexAttribArray ( 2 );

    /* Draw the fragments */
    for (int i = 0; i < RIPPLE_APP_MAX_FRAGMENTS; ++i) {
        if(fragments[i].valid == GL_TRUE) {
            glDrawElements(fragments[i].drawMode, fragments[i].numVertices, GL_UNSIGNED_SHORT,
                           &vertexIndices[fragments[i].startVertexIdx]);
        }
    }
}

void rippleOnTouch (float fPosX, float fPosY) {
    static uint32 lastClickTS = 0u;
    int r = (rand() % 4u);

    if(currTimeDiff(lastClickTS) > 240u) {
        rippleObjInit((GLubyte)r, fPosX, fPosY);
        lastClickTS = currTimeMS();
    }
}

void rippleTimerTask() {
    rippleObjUpdate();
}

void rippleOnInit() {
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


