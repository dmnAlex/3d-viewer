#include "scene.h"

#include "figure.h"

namespace s21 {
void Scene::NormalizeCoordinates(NormalizationParameters norm_params) {
  double x_max = figures_.front().VertexAt(0).GetPosition().x;
  double x_min = x_max;
  double y_max = figures_.front().VertexAt(0).GetPosition().y;
  double y_min = y_max;
  double z_max = figures_.front().VertexAt(0).GetPosition().z;
  double z_min = z_max;
  for (auto& figure : figures_) {
    for (auto& vertex : figure.GetVertices()) {
      double temp = vertex.GetPosition().x;
      if (temp > x_max) x_max = temp;
      if (temp < x_min) x_min = temp;

      temp = vertex.GetPosition().y;
      if (temp > y_max) y_max = temp;
      if (temp < y_min) y_min = temp;

      temp = vertex.GetPosition().z;
      if (temp > z_max) z_max = temp;
      if (temp < z_min) z_min = temp;
    }
  }

  double x_offset = (x_max - x_min) / 2 + x_min;
  double y_offset = (y_max - y_min) / 2 + y_min;
  double z_offset = (z_max - z_min) / 2 + z_min;

  double max_distance = x_max - x_min;
  if (max_distance < y_max - y_min) max_distance = y_max - y_min;
  if (max_distance < z_max - z_min) max_distance = z_max - z_min;

  double scale_factor =
      max_distance / (norm_params.max_coord - norm_params.min_coord);
  for (auto& figure : figures_) {
    for (size_t i = 0; i < figure.GetVerticesCount(); ++i) {
      figure.VertexAt(i).SetX((figure.VertexAt(i).GetPosition().x - x_offset) /
                              scale_factor);
      figure.VertexAt(i).SetY((figure.VertexAt(i).GetPosition().y - y_offset) /
                              scale_factor);
      figure.VertexAt(i).SetZ((figure.VertexAt(i).GetPosition().z - z_offset) /
                              scale_factor);
    }
  }
}

}  // namespace s21
