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

#define  LOG_TAG    "GAME_VIEW"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern float maxWidth;
extern float maxHeight;

typedef enum {
    GAME_SCRIBBLE_APP = 0,
    GAME_RIPPLE_APP,
} gameTypes;

GLuint LoadShader ( GLenum type, const GLchar* shaderSrc );
int InitShaders (GLuint* pProgramObject);

#endif //BABYBOOK_GAMECOMMON_H
