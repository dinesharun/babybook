package com.apps.indudinesh.babybook;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class cGameView extends GLSurfaceView {
    private static native void cOnDraw(int currApp);
    private static native void cOnResize(int currApp, int iWidth, int iHeight);
    private static native void cOnInit(int currApp);
    private static native void cOnTouch(int currApp, float fPosX, float fPosY);

    private static cmnGameActivity.gameTypes currApp = cmnGameActivity.gameTypes.GAME_MAXIMUM;

    private static class cRendererIf implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 gl) {
            cOnDraw(currApp.ordinal());
        }

        public void onSurfaceChanged(GL10 gl, int iWidth, int iHeight) {
            cOnResize(currApp.ordinal(), iWidth, iHeight);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) { cOnInit(currApp.ordinal()); }
    }

    public void onTouch(float fPosX, float fPosY) {
        cOnTouch(currApp.ordinal(), fPosX, fPosY);
        requestRender();
    }

    public cGameView(Context context, cmnGameActivity.gameTypes app) {
        super(context);
        currApp = app;
        /*
        Pick an EGLConfig with RGBA8 color, 16-bit depth, no stencil,
        */
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        setEGLContextClientVersion(2);
        setRenderer(new cRendererIf());
        //setRenderMode(RENDERMODE_WHEN_DIRTY);
    }
}