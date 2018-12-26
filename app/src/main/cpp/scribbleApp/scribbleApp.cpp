/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#include "scribbleApp.h"

float vertexPos[1000][3] = {0.0};
GLushort vertexIdxs[1000] = {0};
int currPos = 0;
GLushort numTriangles = 0;

void scribbleOnDraw(void) {
    // Load the vertex data
    glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, &vertexPos[0][0] );
    glEnableVertexAttribArray ( 0 );

    glVertexAttrib3f(1, 0.0f, 0.0f, 1.0f);
    glEnableVertexAttribArray ( 1 );

    glDrawElements ( GL_TRIANGLE_STRIP, numTriangles, GL_UNSIGNED_SHORT, &vertexIdxs[0] );
}

void scribbleOnTouch (float fPosX, float fPosY) {
    if(currPos != 0) {
        numTriangles += 2;
    }

    vertexPos[currPos][0] = (float)((2.0f * ((fPosX / maxWidth) - 0.5f)) + 0.05f);
    vertexPos[currPos][1] = (float)(2.0f * (0.5f - (fPosY / maxHeight)));
    vertexPos[currPos][2] = 0.0;
    vertexIdxs[currPos] = (GLushort)currPos;
    currPos++;

    vertexPos[currPos][0] = (float)((2.0f * ((fPosX / maxWidth) - 0.5f)) - 0.05f);
    vertexPos[currPos][1] = (float)(2.0f * (0.5f - (fPosY / maxHeight)));
    vertexPos[currPos][2] = 0.0;
    vertexIdxs[currPos] = (GLushort)currPos;
    currPos++;
}

void scribbleOnInit() {
    currPos = 0;
    numTriangles = 0;
}


