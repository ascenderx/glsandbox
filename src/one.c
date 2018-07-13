#include <unistd.h> // usleep

#include <GLFW/glfw3.h>

#include "draw.h"

int main(int argc, char ** argv) {
    GLFWwindow * window;

    // Initialize the library
    if (!glfwInit())
        return 1;
    
    const int WIN_WIDTH  = 640;
    const int WIN_HEIGHT = 480; 
    const int FPS        = 60;
    const char * title   = "GLFW Test One";
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize user code
    uInitEngine();
    uInit2DRenderer(WIN_WIDTH, WIN_HEIGHT);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Update here
        uUpdate();

        // Render here
        uRender2D();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // Sleep before looping
        usleep(1000000 / FPS);
    }

    glfwTerminate();
    return 0;
}
