#include <unistd.h> // usleep

#include <GLFW/glfw3.h>

#include "draw.h"

#define WIN_WIDTH  640
#define WIN_HEIGHT 480

#define FPS 30

int main(int argc, char ** argv) {
    GLFWwindow * window;

    /* Initialize the library */
    if (!glfwInit())
        return 1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "GLFW Tutorial One", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* init */
    uInitEngine();
    uInit2DRenderer(WIN_WIDTH, WIN_HEIGHT);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Update here */
        uUpdate();

        /* Render here */
        uRender2D();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* sleep */
        usleep(1000000 / FPS);
    }

    glfwTerminate();
    return 0;
}