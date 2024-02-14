#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
  glfwInit();

  GLFWwindow* window = glfwCreateWindow(720, 480, "Mandelbrot Set", NULL, NULL);
  glfwMakeContextCurrent(window);

  gladLoadGL(glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    float color = fabs(sin(glfwGetTime()));
    glClearColor(color, color, color, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}