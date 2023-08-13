#ifndef MODEL_VERTEX_H
#define MODEL_VERTEX_H

#include "point_3d.h"
#include "transform_matrix.h"

namespace s21 {
class Vertex {
 public:
  Vertex(const Point3D& position) : position_(position) {}

  const Point3D& GetPosition() const { return position_; }

  void SetPosition(Point3D position) {
    position_.x = position.x;
    position_.y = position.y;
    position_.z = position.z;
  }

  void SetX(double x) { position_.x = x; }
  void SetY(double y) { position_.y = y; }
  void SetZ(double z) { position_.z = z; }

  void Transform(TransformMatrix& matrix) { matrix.TransformPoint(position_); }

 private:
  Point3D position_;
};
}  // namespace s21

#endif  // MODEL_VERTEX_H
