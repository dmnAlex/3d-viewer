#ifndef MODEL_SCENE_H
#define MODEL_SCENE_H

#include "figure.h"
#include "normalization_parametes.h"
#include "transform_matrix.h"

namespace s21 {
class Scene {
 public:
  Scene() {}
  Scene(const std::vector<Figure>& figures) : figures_(figures) {}

  const std::vector<Figure>& GetFigures() const { return figures_; }
  void AddFigure(const Figure& figure) { figures_.push_back(figure); }

  size_t GetVerticesCount() const {
    size_t count = 0;
    for (auto& figure : figures_) {
      count += figure.GetVerticesCount();
    }

    return count;
  }

  size_t GetEdgesCount() const {
    size_t count = 0;
    for (auto& figure : figures_) {
      count += figure.GetEdgesCount();
    }

    return count;
  }

  void TransformFigures(TransformMatrix& matrix) {
    for (auto& figure : figures_) {
      figure.Transform(matrix);
    }
  }

  void NormalizeCoordinates(NormalizationParameters norm_params);

 private:
  std::vector<Figure> figures_;
};
}  // namespace s21

#endif  // MODEL_SCENE_H
