#include "transform_matrix_builder.h"

namespace s21 {
TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(double x_offset,
                                                         double y_offset,
                                                         double z_offset) {
  TransformMatrix matrix;
  matrix(0, 0) = 1;
  matrix(1, 1) = 1;
  matrix(2, 2) = 1;
  matrix(3, 3) = 1;
  matrix(3, 0) = x_offset;
  matrix(3, 1) = y_offset;
  matrix(3, 2) = z_offset;
  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(double x_angle,
                                                             double y_angle,
                                                             double z_angle) {
  TransformMatrix matrix;
  if (x_angle) {
    double angle_rad = x_angle * M_PI / 180;
    matrix(0, 0) = 1;
    matrix(1, 1) = cos(angle_rad);
    matrix(1, 2) = sin(angle_rad);
    matrix(2, 1) = -sin(angle_rad);
    matrix(2, 2) = cos(angle_rad);
    matrix(3, 3) = 1;
  } else if (y_angle) {
    double angle_rad = y_angle * M_PI / 180;
    matrix(0, 0) = cos(angle_rad);
    matrix(0, 2) = -sin(angle_rad);
    matrix(1, 1) = 1;
    matrix(2, 0) = sin(angle_rad);
    matrix(2, 2) = cos(angle_rad);
    matrix(3, 3) = 1;
  } else if (z_angle) {
    double angle_rad = z_angle * M_PI / 180;
    matrix(0, 0) = cos(angle_rad);
    matrix(0, 1) = sin(angle_rad);
    matrix(1, 0) = -sin(angle_rad);
    matrix(1, 1) = cos(angle_rad);
    matrix(2, 2) = 1;
    matrix(3, 3) = 1;
  } else {
    matrix(0, 0) = 1;
    matrix(1, 1) = 1;
    matrix(2, 2) = 1;
    matrix(3, 3) = 1;
  }

  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(double scale) {
  TransformMatrix matrix;
  matrix(0, 0) = scale;
  matrix(1, 1) = scale;
  matrix(2, 2) = scale;
  matrix(3, 3) = 1;
  return matrix;
}

}  // namespace s21
