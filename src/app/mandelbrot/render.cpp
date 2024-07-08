#include "include.hpp"

void mandelbrot_render_callback(App& app) {
  auto& window = app.mandelbrot;

  window.clear();

  window.vao->bind();
  window.shader->use();
  window.shader->set_float("color", window.color);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
