#ifndef MODEL_TRANSFORMATION_MANAGER_H
#define MODEL_TRANSFORMATION_MANAGER_H

#include <cmath>

#include "transformations.h"

namespace s21 {
class TransformationHandler {
 public:
  TransformationHandler() {}
  TransformationHandler(const Transformations& transforms)
      : cur_transforms_(transforms) {}

  void ResetTransformations();
  void HandleScale(double& scale);
  void HandleOffsets(double& x_offset, double& y_offset, double& z_offset);
  void HandleRotationAngles(double& x_angle, double& y_angle, double& z_angle);

  const Transformations& GetCurrentTransfomations() const {
    return cur_transforms_;
  }

 private:
  Transformations cur_transforms_;
};
}  // namespace s21

#endif  // TRANSFORMATION_MANAGER_H
