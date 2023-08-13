#ifndef MODEL_TRANSFORM_MATRIX_H
#define MODEL_TRANSFORM_MATRIX_H

#include <vector>

#include "point_3d.h"

using std::vector;

namespace s21 {
class TransformMatrix {
 public:
  double& operator()(int row, int col) { return matrix_[row][col]; }
  void TransformPoint(Point3D& point);

 private:
  vector<vector<double>> matrix_{4, vector<double>(4)};
};
}  // namespace s21

#endif  // MODEL_TRANSFORM_MATRIX_H
