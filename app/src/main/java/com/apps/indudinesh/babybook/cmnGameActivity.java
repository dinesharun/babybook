/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

package com.apps.indudinesh.babybook;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;

import java.util.Timer;
import java.util.TimerTask;

/**
 * A simple scribble pad.
 */
public class cmnGameActivity extends AppCompatActivity {

    private static native void cTimerTask(int currApp);

    public enum gameTypes {
        GAME_SCRIBBLE_APP,
        GAME_RIPPLE_APP,
        GAME_MAXIMUM
    }
    /**
     * C++ NDK gameView wrapper.
     */
    private cGameView mGLView;
    private Timer animTimer;
    private TimerTask timerTask;
    private gameTypes currApp = gameTypes.GAME_MAXIMUM;

    /**
     * Load the c++ NDK game viewer.
     */
    static {
        System.loadLibrary("cGameViewLib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent intent = getIntent();
        currApp = (gameTypes) intent.getSerializableExtra("currApp");

        /** Create a cGameView instance and set it
         *  as the ContentView for this Activity.
         */
        mGLView = new cGameView(this, currApp);
        setContentView(mGLView);

        /* Create, init and start the timer */
        animTimer = new Timer();
        timerTask = new TimerTask() {
            @Override
            public void run() {
                cTimerTask(currApp.ordinal());
            }
        };
        animTimer.schedule(timerTask, 100, 100);
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        int action = e.getActionMasked();
        boolean release = false;
        if (action == MotionEvent.ACTION_UP) {
            release = true;
        }
        super.onTouchEvent(e);
        mGLView.onTouch(e.getX(), e.getY(),release);
        return true;
    }

    @Override
    protected void onPause()
    {
        //animTimer.purge();
        //animTimer.cancel();
        super.onPause();
        mGLView.onPause();
    }

    @Override
    protected void onResume()
    {
        //animTimer.schedule(timerTask, 300, 300);
        super.onResume();
        mGLView.onResume();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus) {
            hideSystemUI();
        }
    }

    private void hideSystemUI() {
        // Enables regular immersive mode.
        // For "lean back" mode, remove SYSTEM_UI_FLAG_IMMERSIVE.
        // Or for "sticky immersive," replace it with SYSTEM_UI_FLAG_IMMERSIVE_STICKY
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_IMMERSIVE
                        // Set the content to appear under the system bars so that the
                        // content doesn't resize when the system bars hide and show.
                        | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        // Hide the nav bar and status bar
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_FULLSCREEN);
    }

    // Shows the system bars by removing all the flags
    // except for the ones that make the content appear under the system bars.
    private void showSystemUI() {
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN);
    }
}
