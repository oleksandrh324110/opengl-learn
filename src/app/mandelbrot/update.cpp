#include "include.hpp"

void mandelbrot_update_callback(App& app) {
  auto& window = app.mandelbrot;

  const float aspect = window.size.x / window.size.y;

  static glm::vec2 top_left = glm::vec2(-1, 1);
  static glm::vec2 bottom_right = glm::vec2(1, -1);
  static float hue_shift = 0.5;
  static float zoom = 1;
  static float smooth_zoom = 1;
  static int max_iterations = 256;

  if (window.mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down)
    window.central_point -=
        glm::vec2(window.mouse.delta.x * aspect, window.mouse.delta.y) * 2.f / window.size / zoom;

  if (window.mouse.zoom.y == 1)
    zoom *= 1.5;
  else if (window.mouse.zoom.y == -1)
    zoom /= 1.5;

  zoom = std::max(0.1f, zoom);
  max_iterations = std::max(1, max_iterations);

  smooth_zoom = glm::mix(smooth_zoom, zoom, window.delta_time * 10);

  float width = (bottom_right.x - top_left.x) / smooth_zoom;
  float height = (top_left.y - bottom_right.y) / smooth_zoom;

  glm::vec2 new_top_left = window.central_point + glm::vec2(-width / 2 * aspect, height / 2);
  glm::vec2 new_bottom_right = window.central_point + glm::vec2(width / 2 * aspect, -height / 2);

  window.shader->use();
  window.shader->set_uniform("resolution", window.size);
  window.shader->set_uniform("top_left", new_top_left);
  window.shader->set_uniform("bottom_right", new_bottom_right);
  window.shader->set_uniform("hue_shift", hue_shift);
  window.shader->set_uniform("max_iterations", max_iterations);
  window.shader->set_uniform("pow", app.pow);

  ImGui::Begin("Mandelbrot Set");
  ImGui::Text("Central point: (%f, %f)", window.central_point.x, window.central_point.y);
  ImGui::InputInt("Max Iterations", &max_iterations, 1, 10);
  ImGui::SliderFloat("Pow", &app.pow, 1, 10);
  ImGui::SliderFloat("Hue shift", &hue_shift, 0, 1);
  if (ImGui::Button("Exit"))
    window.set_should_close(true);
  ImGui::End();
}
