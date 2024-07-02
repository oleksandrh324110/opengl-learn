#pragma once

#include "../utils/utils.hpp"
#include "vbo.hpp"

class VAO {
 public:
  GLuint handle;

  VAO();
  ~VAO();

  void bind() const;
  void attr(VBO& vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) const;
};
