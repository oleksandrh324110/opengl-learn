#pragma once

#include "../utils/utils.hpp"

class VBO {
 public:
  GLuint handle;
  GLint type;
  bool dynamic;

  VBO(GLint type, bool dynamic);
  ~VBO();

  void bind() const;
  void buffer(void* data, size_t size) const;
};
