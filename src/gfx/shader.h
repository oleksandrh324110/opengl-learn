#pragma once

#include "../util/util.h"
#include "gfx.h"

struct VertexAttr {
  GLuint index;
  const GLchar *name;
};

struct Shader {
  GLuint handle, vs_handle, fs_handle;
};

struct Shader shader_create(const char *vs_path, const char *fs_path, struct VertexAttr[]);
void shader_destroy(struct Shader self);
void shader_bind(struct Shader self);
void shader_uniform_mat4(struct Shader self, const char *name, mat4 m);
// void shader_uniform_view_proj(struct Shader self, struct ViewProj view_proj);
// void shader_uniform_texture2d(struct Shader self, const char *name, struct Texture Texture, GLuint n);
void shader_uniform_float(struct Shader self, const char *name, float f);
void shader_uniform_vec2(struct Shader self, const char *name, vec2 v);
void shader_uniform_vec3(struct Shader self, const char *name, vec3 v);
void shader_uniform_vec4(struct Shader self, const char *name, vec4 v);
void shader_uniform_int(struct Shader self, const char *name, int v);
void shader_uniform_uint(struct Shader self, const char *name, unsigned int v);