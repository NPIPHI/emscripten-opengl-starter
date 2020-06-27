#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "loadShader.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

//these are in the global scope for emscripten compatibility
GLFWwindow* window;
GLuint programID;
GLuint vertexbuffer;
GLuint vertexArrayID;
GLuint vertexPosition;

void cleanUp();
void mainLoop();
void glInit();

int main( void ){
    glInit();

    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "res/vertex.glsl", "res/fragment.glsl" );

    //fill vertex buffer with triangle
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    vertexPosition = glGetAttribLocation(programID, "vertexPosition");

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, 1);
#else
	do{
	    mainLoop();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
    cleanUp();
#endif
    return 0;
}

void glInit(){
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Opengl Triangle", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

}

void mainLoop(){
    //make the tip of the triangle follow the cursor
    double x, y;
    int width, height;
    glfwGetCursorPos(window, &x, &y);
    glfwGetWindowSize(window, &width, &height);
    float screenX = x / width * 2 - 1;
    float screenY = -(y / height * 2 - 1);
    float point[] = {
            screenX, screenY, 0
    };
    glBufferSubData(GL_ARRAY_BUFFER, 24, 12, point);

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );

    // Use our shader
    glUseProgram(programID);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(vertexPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            vertexPosition,                  // location of our vertex attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized, does not matter when input type is float
            0,                  // stride
            (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void cleanUp(){
    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &vertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}