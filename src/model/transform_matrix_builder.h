#ifndef MODEL_TRANSFORM_MATRIX_BUILDER_H
#define MODEL_TRANSFORM_MATRIX_BUILDER_H

#include <math.h>

#include "transform_matrix.h"

namespace s21 {
class TransformMatrixBuilder {
 public:
  static TransformMatrix CreateRotationMatrix(double x_angle, double y_angle,
                                              double z_angle);
  static TransformMatrix CreateMoveMatrix(double x_offset, double y_offset,
                                          double z_offset);
  static TransformMatrix CreateScaleMatrix(double new_scale);
};
}  // namespace s21

#endif  // MODEL_TRANSFORM_MATRIX_BUILDER_H
