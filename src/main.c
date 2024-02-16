#include "gfx/gfx.h"
#include "util/util.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main(void) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *const video_mode = glfwGetVideoMode(monitor);

  GLFWwindow *window = glfwCreateWindow(video_mode->width, video_mode->height, "Mandelbrot Set", monitor, NULL);
  glfwMakeContextCurrent(window);

  gladLoadGL(glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    float color = fabs(sin(glfwGetTime()));
    glClearColor(color, color, color, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  UNUSED(window);
  glViewport(0, 0, width, height);
}
