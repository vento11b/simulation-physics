#include <GLFW/glfw3.h>
#include <stdio.h>

static void error_callback(int error, const char* desc)
{
    printf("GLFW error %d: %s\n", error, desc);
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    
    /* Initialize the library */

    if (!glfwInit()) {
        printf("glfwInit falló\n");
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        printf("glfwInit falló\n");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}