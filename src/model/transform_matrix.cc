#include "transform_matrix.h"

namespace s21 {

void TransformMatrix::TransformPoint(Point3D& point) {
  double x = point.x * matrix_[0][0] + point.y * matrix_[1][0] +
             point.z * matrix_[2][0] + matrix_[3][0];
  double y = point.x * matrix_[0][1] + point.y * matrix_[1][1] +
             point.z * matrix_[2][1] + matrix_[3][1];
  double z = point.x * matrix_[0][2] + point.y * matrix_[1][2] +
             point.z * matrix_[2][2] + matrix_[3][2];
  point.x = x;
  point.y = y;
  point.z = z;
}

}  // namespace s21
