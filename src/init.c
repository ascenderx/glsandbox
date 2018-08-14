#include <unistd.h> // usleep
#include <GLFW/glfw3.h>

#define TITLE_MAX_LENGTH 256
#define EXIT_SUCCESS     0
#define EXIT_ERROR       1

#ifndef bool
typedef char bool;
bool false = 0;
bool true  = 1;
#endif // bool

struct Settings {
    int  winWidth;
    int  winHeight;
    char title[TITLE_MAX_LENGTH];
    int  framerate;
    void (* init)(void);
    void (* input)(void);
    void (* update)(void);
    void (* render)(void);
    GLFWwindow * window;
};

bool utilInit(struct Settings * stgs) {
    if (!glfwInit()) {
        return false;
    }
    
    stgs->window = glfwCreateWindow(stgs->winWidth, stgs->winHeight, stgs->title, NULL, NULL);
    if (!stgs->window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(stgs->window);

    // init user data
    if (stgs->init) {
        stgs->init();
    }

    return true;
}

bool utilRun(struct Settings * stgs) {
    if (!stgs->input || !stgs->update || !stgs->render) {
        return false;
    }

    while (!glfwWindowShouldClose(stgs->window)) {
        glfwPollEvents();

        // run user functions
        stgs->input();
        stgs->update();
        stgs->render();

        glfwSwapBuffers(stgs->window);

        usleep(1000000 / stgs->framerate);
    }

    glfwTerminate();

    return true;
}
