/**
 * Copyright 2018, Dinesh Arun Kasipandian & Indumathi Duraipandian.
 *
 * Part of the "Babybook" Android application (A open & free openGL based
 * simple games aimed at toddlers.
 *
 */

#include "gameCommon.h"

///
// Create a shader object, load the shader source, and
// compile the shader.
//
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

///
// Initialize the shader and program object
//
int InitShaders (GLuint* pProgramObject)
{
    GLchar vShaderStr[] =
            "attribute vec4 vPosition;    \n"
            "void main()                  \n"
            "{                            \n"
            "   gl_Position = vPosition;  \n"
            "}                            \n";

    GLchar fShaderStr[] =
            "precision mediump float;\n"\
            "void main()                                  \n"
            "{                                            \n"
            "  gl_FragColor = vec4 ( 0.0, 0.0, 0.0, 1.0 );\n"
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

    // Bind vPosition to attribute 0
    glBindAttribLocation ( (*pProgramObject), 0, "vPosition" );

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