#include <jni.h>
#include "gameCommon.h"
#include "scribbleApp.h"

float maxWidth;
float maxHeight;

static GLuint pgmObj;

extern "C" JNIEXPORT void JNICALL
Java_com_apps_indudinesh_babybook_cGameView_cOnDraw(
        JNIEnv* env,
        jobject /* this */,
        jint currApp) {

    /* Use the program object */
    glUseProgram ( pgmObj );

    /* Clear once again  */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepthf(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (currApp) {
        case GAME_SCRIBBLE_APP: {
            scribbleOnDraw();
            break;
        } case GAME_RIPPLE_APP: {
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
    glViewport(0, 0, iWidth, iHeight);
}

extern "C" JNIEXPORT void JNICALL
Java_com_apps_indudinesh_babybook_cGameView_cOnTouch(
        JNIEnv* env,
        jobject /* this */,
        jint currApp,
        jfloat fPosX,
        jfloat fPosY) {

    switch (currApp) {
        case GAME_SCRIBBLE_APP: {
            scribbleOnTouch(fPosX, fPosY);
            break;
        } case GAME_RIPPLE_APP: {
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
}
