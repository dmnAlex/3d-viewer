#ifndef MODEL_TRANSFORMATIONS_H
#define MODEL_TRANSFORMATIONS_H

namespace s21 {
struct Transformations {
  double scale = 1.0;
  double x_offset = 0;
  double y_offset = 0;
  double z_offset = 0;
  int x_angle = 0;
  int y_angle = 0;
  int z_angle = 0;
};
}  // namespace s21

#endif  // MODEL_TRANSFORMATIONS_H
