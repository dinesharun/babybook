/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#include "scribbleApp/scribbleApp.h"
#include "rippleApp/rippleApp.h"

float maxWidth;
float maxHeight;
float aspectRatio;

GLuint pgmObj;

extern "C" JNIEXPORT void JNICALL
Java_com_apps_indudinesh_babybook_cGameView_cOnDraw(
        JNIEnv* env,
        jobject /* this */,
        jint currApp) {

    /* Use the program object */
    glUseProgram ( pgmObj );

    setOrthoProjection();

    /* Clear once again  */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepthf(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (currApp) {
        case GAME_SCRIBBLE_APP: {
            scribbleOnDraw();
            break;
        } case GAME_RIPPLE_APP: {
            rippleOnDraw();
            break;
        } default: {
            break;
        }
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_apps_indudinesh_babybook_cGameView_cOnResize(
        JNIEnv* env,
        jobject /* this */,
        jint currApp,
        jint iWidth,
        jint iHeight) {

    /* Set the sizes as required */
    maxWidth = (float)iWidth;
    maxHeight = (float)iHeight;
    aspectRatio = maxHeight / maxWidth;
    glViewport(0, 0, iWidth, iHeight);
}

extern "C" JNIEXPORT void JNICALL
Java_com_apps_indudinesh_babybook_cmnGameActivity_cTimerTask(
        JNIEnv* env,
        jobject /* this */,
        jint currApp) {
    switch (currApp) {
        case GAME_SCRIBBLE_APP: {
            break;
        } case GAME_RIPPLE_APP: {
            rippleTimerTask();
            break;
        } default: {
            break;
        }
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_apps_indudinesh_babybook_cGameView_cOnTouch(
        JNIEnv* env,
        jobject /* this */,
        jint currApp,
        jfloat fPosX,
        jfloat fPosY,
        jboolean release) {

    switch (currApp) {
        case GAME_SCRIBBLE_APP: {
            scribbleOnTouch(fPosX, fPosY,release);
            break;
        } case GAME_RIPPLE_APP: {
            rippleOnTouch(fPosX, fPosY);
            break;
        } default: {
            break;
        }
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_apps_indudinesh_babybook_cGameView_cOnInit(
        JNIEnv* env,
        jobject /* this */,
        jint currApp) {

    /* Clear color buffer with white */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepthf(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Create, compile, link and create the shaders */
    InitShaders(&pgmObj);

    switch (currApp) {
        case GAME_SCRIBBLE_APP: {
            scribbleOnInit();
            break;
        } case GAME_RIPPLE_APP: {
            rippleOnInit();
            break;
        } default: {
            break;
        }
    }
}
