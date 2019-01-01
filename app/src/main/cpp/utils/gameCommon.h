/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#ifndef BABYBOOK_GAMECOMMON_H
#define BABYBOOK_GAMECOMMON_H

#include <stdlib.h>
#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#include <iostream>
#include <math.h>
#include "matrix.h"


extern GLuint pgmObj;
extern float maxWidth;
extern float maxHeight;
extern float aspectRatio;

#define  LOG_TAG    "GAME_VIEW"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define SCREEN_TO_PLANE_X(x) ((float) ((2.0f * ((x / maxWidth) - 0.5f))))
#define SCREEN_TO_PLANE_Y(y) ((float) (2.0f * aspectRatio * (0.5f - (y / maxHeight))))


typedef enum {
    GAME_SCRIBBLE_APP = 0,
    GAME_RIPPLE_APP,
} gameTypes;

typedef struct {
    float position[3];
    GLubyte color[4];
} verticeInfo;

typedef struct {
    GLenum drawMode;
    GLushort numTriangles;
    GLushort startVertexIdx;
    GLushort numVertices;
    bool valid;
    GLbyte padding[1];
} fragmentInfo;

typedef struct {
    verticeInfo* vertices;
    fragmentInfo* fragments;
    GLushort* vertexIndices;
    GLushort currVertexIdx;
    GLushort maxVertices;
    GLushort maxFragments;
} renderData;

typedef struct {
    float radius;
    float width;
    float height;
    GLuint color;
    GLubyte colorMode;
} shapeInfo;

GLuint LoadShader ( GLenum type, const GLchar* shaderSrc );
int InitShaders (GLuint* pProgramObject);

void setOrthoProjection(void);
GLushort getNextFreeFragment(fragmentInfo* pFragments, GLushort maxFragments);
PMAT getOrthoProjectionMatrix(float l, float r, float t, float b, float n, float f);

void drawCircle(renderData* d, float x, float y, float z, shapeInfo s);
void drawDiamond(renderData* d, float x, float y, float z, shapeInfo s);
void drawPentagon(renderData* d, float x, float y, float z, shapeInfo s);
void drawHexagon(renderData* d, float x, float y, float z, shapeInfo s);

void drawFilledCircle(renderData* d, float x, float y, float z, shapeInfo s);
void drawFilledDiamond(renderData* d, float x, float y, float z, shapeInfo s);
void drawFilledPentagon(renderData* d, float x, float y, float z, shapeInfo s);
void drawFilledHexagon(renderData* d, float x, float y, float z, shapeInfo s);

#endif //BABYBOOK_GAMECOMMON_H
