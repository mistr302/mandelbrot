#include "glad/include/glad/glad.h"
// #include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
char *read_file(char *fname) {
  FILE *f = fopen(fname, "r");
  if (!f) { /* Handle error */
    printf("couldnt read file %s\n", fname);
    exit(EXIT_FAILURE);
  }

  fseek(f, 0, SEEK_END);
  long size = ftell(f) + 1;
  rewind(f);

  char *read = malloc(size);
  if (fread(read, 1, size - 1, f) != size - 1) { /* Handle error */
  }
  read[size - 1] = '\0'; // Null-terminate
  fclose(f);

  printf("%s", read);
  return read;
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
int main(int argc, char *argv[]) {
  // gl
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
  // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    glfwTerminate();
    return -1;
  }
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  char *vertexShaderSource = read_file("src/shaders/vertex.glsl");

  glShaderSource(vertexShader, 1, (const char **)&vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  char *fragmentShaderSource = read_file("src/shaders/fragment.glsl");

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, (const char **)&fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
  // *)0); glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // while (!glfwWindowShouldClose(window)) {
  //   glClear(GL_COLOR_BUFFER_BIT); // Clear to black
  //   glUseProgram(shaderProgram);
  //   glDrawArrays(GL_TRIANGLES, 0, 3);
  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
  // }
  return EXIT_SUCCESS;
}
