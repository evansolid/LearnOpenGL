#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/shader.h"

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile the shader program
    Shader ourShader("include/shader/shader.vs", "include/shader/shader.fs");

    // set up the vertex data and buffers and configure vertex attributes
    float firstTriangle[] = {
        // positions       colors
        0.1f,  0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 
        0.9f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f,  
        0.1f, -0.7f, 0.0f, 0.0f, 1.0f, 0.0f
    };
    float secondTriangle[] = {
        0.1f,  0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.9f,  0.1f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.9f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // first triangle setup
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second triangle setup
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // this unbinds the VAO so other calls don't accidentally modify it, but this is apparently rare so it is not always necessary.
    glBindVertexArray(0);

    // comment or uncomment this line for wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // rendering loop while the window is open
    while(!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // for the first triangle, use first shader
        ourShader.use();

        // render the triangles
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES,0, 3);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap the buffers and poll IO events (key presses and more)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocate resources once they've outlived their purpose
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    
    // glfw: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant kays are pressed this frame and react accordingly

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// glfw: whenever the window size changes, this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport mtches the new window dimensions
    glViewport(0, 0, width, height);
}