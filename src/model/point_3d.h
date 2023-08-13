#ifndef MODEL_POINT_3D_H
#define MODEL_POINT_3D_H

namespace s21 {
struct Point3D {
  Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

  double x;
  double y;
  double z;
};
}  // namespace s21

#endif  // MODEL_POINT_3D_H
