#include "shader.h"

static GLint _compile(const char *path, GLenum type) {
  FILE *file;
  const char *src;
  int len;

  file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "error loading shader at %s\n", path);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  len = ftell(file);
  fseek(file, 0, SEEK_SET);

  src = malloc(len);
  fread(src, 1, len, file);

  fclose(file);

  GLuint handle = glCreateShader(type);
  glShaderSource(handle, 1, src, len);
  glCompileShader(handle);
}

struct Shader shader_create(const char *vs_path, const char *fs_path, struct VertexAttr[]) {}