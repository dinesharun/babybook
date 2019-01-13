/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#include "gameCommon.h"

static void drawLoop(renderData* d, float x, float y, float z, shapeInfo s, GLbyte resolution);
static void drawThickLoop(renderData* d, float x, float y, float z, shapeInfo s, GLbyte resolution);
static void drawFilledLoop(renderData* d, float x, float y, float z, shapeInfo s, GLbyte resolution);

GLuint LoadShader ( GLenum type, const GLchar* const shaderSrc )
{
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader ( type );

    if ( shader == 0 )
        return 0;

    // Load the shader source
    glShaderSource ( shader, 1, &shaderSrc, NULL );

    // Compile the shader
    glCompileShader ( shader );

    // Check the compile status
    glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

    if ( !compiled )
    {
        GLint infoLen = 0;

        glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

        if ( infoLen > 1 )
        {
            char* infoLog = (char*)malloc (sizeof(char) * infoLen );

            glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
            LOGD( "Error compiling shader:\n%s\n", infoLog );

            free ( infoLog );
        }

        glDeleteShader ( shader );
        return 0;
    }

    return shader;

}

int InitShaders (GLuint* pProgramObject)
{
    GLchar vShaderStr[] =
            "attribute vec3 vPosition;                  \n"
            "attribute vec4 vColor;                     \n"
            "uniform mat4 vMVPMatrix;                   \n"
            "varying vec4 iColor;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position =  vMVPMatrix * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);   \n"
            "   iColor = vColor;                        \n"
            "}                                          \n";

    GLchar fShaderStr[] =
            "precision mediump float;                     \n"
            "varying vec4 iColor;                         \n"
            "void main()                                  \n"
            "{                                            \n"
            "  gl_FragColor = iColor;                     \n"
            "}                                            \n";

    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader ( GL_VERTEX_SHADER, &vShaderStr[0] );
    fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, &fShaderStr[0] );

    // Create the program object
    (*pProgramObject) = glCreateProgram ( );

    if ( (*pProgramObject) == 0 )
        return 0;

    glAttachShader ( (*pProgramObject), vertexShader );
    glAttachShader ( (*pProgramObject), fragmentShader );

    // Bind attributes to positions
    glBindAttribLocation ( (*pProgramObject), 0, "vPosition" );
    glBindAttribLocation ( (*pProgramObject), 1, "vNormal" );
    glBindAttribLocation ( (*pProgramObject), 2, "vColor" );

    // Link the program
    glLinkProgram ( (*pProgramObject) );

    // Check the link status
    glGetProgramiv ( (*pProgramObject), GL_LINK_STATUS, &linked );

    if ( !linked )
    {
        GLint infoLen = 0;

        glGetProgramiv ( (*pProgramObject), GL_INFO_LOG_LENGTH, &infoLen );

        if ( infoLen > 1 )
        {
            char* infoLog = (char*)malloc (sizeof(char) * infoLen );

            glGetProgramInfoLog ( (*pProgramObject), infoLen, NULL, infoLog );
            LOGD( "Error linking program:\n%s\n", infoLog );

            free ( infoLog );
        }

        glDeleteProgram ( (*pProgramObject) );
        return GL_FALSE;
    }

    glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

    return GL_TRUE;
}

GLushort getNextFreeFragment(fragmentInfo* pFragments, GLushort maxFragments) {
    for(int i = 0; i < maxFragments; i++) {
        if(pFragments[i].valid == GL_FALSE) {
            return (GLushort)i;
        }
    }

    return maxFragments;
}

void setOrthoProjection() {
    int mvpLoc;
    PMAT mvpMatrix;

    /* Set the MVP matrix */
    if ((mvpLoc = glGetUniformLocation(pgmObj, "vMVPMatrix")) >= 0) {
        mvpMatrix = getOrthoProjectionMatrix(-1.0f, 1.0f, aspectRatio, -aspectRatio, -1.0f, 1.0f);
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (GLfloat*)mvpMatrix->values);
        destroyMatrix(mvpMatrix);
    } else {
        GLenum error = glGetError();
        LOGD("Location not found: %d", error);
    }
};

PMAT getOrthoProjectionMatrix(float l, float r, float t, float b, float n, float f) {
    PMAT ortho;

    ortho = createMatrix(4, 4);

    MAT(ortho, 0, 0) = ((2.0f) / (r - l));
    MAT(ortho, 1, 1) = ((2.0f) / (t - b));
    MAT(ortho, 2, 2) = ((-2.0f) / (f - n));
    MAT(ortho, 0, 3) = ((-1.0f) * ((r + l) / (r - l)));
    MAT(ortho, 1, 3) = ((-1.0f) * ((t + b) / (t - b)));
    MAT(ortho, 2, 3) = ((-1.0f) * ((f + n) / (f - n)));
    MAT(ortho, 3, 3) = (1.0f);

    return ortho;
}

void drawFilledCircle(renderData* d, float x, float y, float z, shapeInfo s) {
    drawFilledLoop(d, x, y, z, s, 32);
}

void drawThickCircle(renderData* d, float x, float y, float z, shapeInfo s) {
    drawThickLoop(d, x, y, z, s, 32);
}

void drawCircle(renderData* d, float x, float y, float z, shapeInfo s) {
    drawLoop(d, x, y, z, s, 32);
}

void drawFilledDiamond(renderData* d, float x, float y, float z, shapeInfo s) {
    drawFilledLoop(d, x, y, z, s, 4);
}

void drawThickDiamond(renderData* d, float x, float y, float z, shapeInfo s) {
    drawThickLoop(d, x, y, z, s, 4);
}

void drawDiamond(renderData* d, float x, float y, float z, shapeInfo s) {
    drawLoop(d, x, y, z, s, 4);
}

void drawFilledPentagon(renderData* d, float x, float y, float z, shapeInfo s) {
    drawFilledLoop(d, x, y, z, s, 8);
}

void drawThickPentagon(renderData* d, float x, float y, float z, shapeInfo s) {
    drawThickLoop(d, x, y, z, s, 8);
}

void drawPentagon(renderData* d, float x, float y, float z, shapeInfo s) {
    drawLoop(d, x, y, z, s, 8);
}

void drawFilledHexagon(renderData* d, float x, float y, float z, shapeInfo s) {
    drawFilledLoop(d, x, y, z, s, 8);
}

void drawThickHexagon(renderData* d, float x, float y, float z, shapeInfo s) {
    drawThickLoop(d, x, y, z, s, 8);
}

void drawHexagon(renderData* d, float x, float y, float z, shapeInfo s) {
    drawLoop(d, x, y, z, s, 8);
}

static void drawLoop(renderData* d, float x, float y, float z, shapeInfo s, GLbyte resolution) {
    /* Resolution is to be a power of 2 and should be at-least 4*/
    if((resolution < 4u) || ((resolution) & (resolution - 1u))) {
        /* When not set resolution to 4 (minimum) */
        resolution = 4u;
    }

    int fragmentIdx;

    /* If free fragment space available */
    if((fragmentIdx = getNextFreeFragment(&d->fragments[0], d->maxFragments)) < d->maxFragments) {
        /* Set fragment basic parameters */
        d->fragments[fragmentIdx].valid = GL_TRUE;
        d->fragments[fragmentIdx].drawMode = GL_LINE_LOOP;
        d->fragments[fragmentIdx].startVertexIdx = d->currVertexIdx;
        d->fragments[fragmentIdx].numTriangles = (GLushort)(0u);
        d->fragments[fragmentIdx].numVertices = (GLushort)(resolution);

        /* For the given resolution */
        for (int i = 0; i < resolution; i++) {
            /* Add outer vertices of the loop at every spoke of the resolution */
            d->vertices[d->currVertexIdx].position[0] =
                    SCREEN_TO_PLANE_X(x) + (s.radius * (sin((float) (2.0 * M_PI * ((float)i / (float)resolution)))));
            d->vertices[d->currVertexIdx].position[1] =
                    SCREEN_TO_PLANE_Y(y) + (s.radius * (cos((float) (2.0 * M_PI * ((float)i / (float)resolution)))));
            d->vertices[d->currVertexIdx].position[2] = z;
            /* Derive vertex colors from the given color */
            d->vertices[d->currVertexIdx].color[0] =  ((s.color & 0x000000ffu) / 255.0f);
            d->vertices[d->currVertexIdx].color[1] =  (((s.color & 0x0000ff00u) >> 8) / 255.0f);
            d->vertices[d->currVertexIdx].color[2] =  (((s.color & 0x00ff0000u) >> 16) / 255.0f);
            d->vertices[d->currVertexIdx].color[3] =  ((0xffu) / 255.0f);
            /* Set vertex index and move to next vertex */
            d->vertexIndices[d->currVertexIdx] = (GLushort) d->currVertexIdx;
            d->currVertexIdx++;
        }
    }
}

static void drawThickLoop(renderData* d, float x, float y, float z, shapeInfo s, GLbyte resolution) {
    /* Resolution is to be a power of 2 and should be at-least 4*/
    if((resolution < 4u) || ((resolution) & (resolution - 1u))) {
        /* When not set resolution to 4 (minimum) */
        resolution = 4u;
    }

    int fragmentIdx;

    /* If free fragment space available */
    if((fragmentIdx = getNextFreeFragment(&d->fragments[0], d->maxFragments)) < d->maxFragments) {
        /* Set fragment basic parameters */
        d->fragments[fragmentIdx].valid = GL_TRUE;
        d->fragments[fragmentIdx].drawMode = GL_TRIANGLE_STRIP;
        d->fragments[fragmentIdx].startVertexIdx = d->currVertexIdx;
        d->fragments[fragmentIdx].numTriangles = (GLushort)(0u);
        d->fragments[fragmentIdx].numVertices = (GLushort)((resolution + 1u) * 2u);

        /* For the given resolution */
        for (int i = 0; i < resolution; i++) {
            /* For the outer and inner shell of the loop */
            for(int j = 1; j >= 0; j--) {
                /* Add outer vertices of the loop at every spoke of the resolution */
                d->vertices[d->currVertexIdx].position[0] =
                        SCREEN_TO_PLANE_X(x) +
                        ((s.radius + (s.thickness * j)) * (sin((float) (2.0 * M_PI * ((float) i / (float) resolution)))));
                d->vertices[d->currVertexIdx].position[1] =
                        SCREEN_TO_PLANE_Y(y) +
                        ((s.radius + (s.thickness * j)) * (cos((float) (2.0 * M_PI * ((float) i / (float) resolution)))));
                d->vertices[d->currVertexIdx].position[2] = z;
                /* Derive the color of the vertex from the given color */
                d->vertices[d->currVertexIdx].color[0] =  ((s.color & 0x000000ffu) / 255.0f);
                d->vertices[d->currVertexIdx].color[1] =  (((s.color & 0x0000ff00u) >> 8) / 255.0f);
                d->vertices[d->currVertexIdx].color[2] =  (((s.color & 0x00ff0000u) >> 16) / 255.0f);
                d->vertices[d->currVertexIdx].color[3] =  ((0xffu) / 255.0f);
                /* Set current vertex index and move to next vertex */
                d->vertexIndices[d->currVertexIdx] = (GLushort) d->currVertexIdx;
                d->currVertexIdx++;
            }
        }

        d->vertexIndices[d->currVertexIdx++] = d->fragments[fragmentIdx].startVertexIdx;
        d->vertexIndices[d->currVertexIdx++] = d->fragments[fragmentIdx].startVertexIdx + (GLushort)1u;
    }
}

static void drawFilledLoop(renderData* d, float x, float y, float z, shapeInfo s, GLbyte resolution) {
    /* Resolution is to be a power of 2 and should be at-least 4*/
    if((resolution < 4u) || ((resolution) & (resolution - 1u))) {
        /* When not set resolution to 4 (minimum) */
        resolution = 4u;
    }

    int fragmentIdx;

    /* If free fragment space available */
    if((fragmentIdx = getNextFreeFragment(&d->fragments[0], d->maxFragments)) < d->maxFragments) {
        /* Set fragment basic parameters */
        d->fragments[fragmentIdx].valid = GL_TRUE;
        d->fragments[fragmentIdx].drawMode = GL_TRIANGLE_FAN;
        d->fragments[fragmentIdx].startVertexIdx = d->currVertexIdx;
        d->fragments[fragmentIdx].numTriangles = (GLushort)(resolution);
        d->fragments[fragmentIdx].numVertices = (GLushort)(resolution + 2u);

        /* Add center vertex position */
        d->vertices[d->currVertexIdx].position[0] = SCREEN_TO_PLANE_X(x);
        d->vertices[d->currVertexIdx].position[1] = SCREEN_TO_PLANE_Y(y);
        d->vertices[d->currVertexIdx].position[2] = z;
        /* Set center vertex color */
        d->vertices[d->currVertexIdx].color[0] =  ((s.color & 0x000000ffu) / 255.0f);
        d->vertices[d->currVertexIdx].color[1] =  (((s.color & 0x0000ff00u) >> 8) / 255.0f);
        d->vertices[d->currVertexIdx].color[2] =  (((s.color & 0x00ff0000u) >> 16) / 255.0f);
        d->vertices[d->currVertexIdx].color[3] =  ((0xffu) / 255.0f);
        /* Set center vertex position and move to next vertex */
        d->vertexIndices[d->currVertexIdx] = (GLushort) d->currVertexIdx;
        d->currVertexIdx++;

        /* For the given resolution */
        for (int i = 0; i <= resolution; i++) {
            /* Add outer vertices at every spoke of the resolution */
            d->vertices[d->currVertexIdx].position[0] =
                    SCREEN_TO_PLANE_X(x) + (s.radius * (sin((float) (2.0 * M_PI * ((float)i / (float)resolution)))));
            d->vertices[d->currVertexIdx].position[1] =
                    SCREEN_TO_PLANE_Y(y) + (s.radius * (cos((float) (2.0 * M_PI * ((float)i / (float)resolution)))));
            d->vertices[d->currVertexIdx].position[2] = z;
            /* Derive the vertex color from the given color */
            d->vertices[d->currVertexIdx].color[0] =  ((s.color & 0x000000ffu) / 255.0f);
            d->vertices[d->currVertexIdx].color[1] =  (((s.color & 0x0000ff00u) >> 8) / 255.0f);
            d->vertices[d->currVertexIdx].color[2] =  (((s.color & 0x00ff0000u) >> 16) / 255.0f);
            d->vertices[d->currVertexIdx].color[3] =  ((0xffu) / 255.0f);
            /* Set vertex position and move to next vertex */
            d->vertexIndices[d->currVertexIdx] = (GLushort) d->currVertexIdx;
            d->currVertexIdx++;
        }
    }
}