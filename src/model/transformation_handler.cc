

#include "transformation_handler.h"

namespace s21 {
void TransformationHandler::ResetTransformations() {
  cur_transforms_.scale = 1.0;
  cur_transforms_.x_offset = 0;
  cur_transforms_.y_offset = 0;
  cur_transforms_.z_offset = 0;
  cur_transforms_.x_angle = 0;
  cur_transforms_.y_angle = 0;
  cur_transforms_.z_angle = 0;
}

void s21::TransformationHandler::HandleScale(double &scale) {
  double handled_scale = 1.0;
  if (scale < 0) {
    handled_scale = 1 / std::abs(scale) / cur_transforms_.scale;
    cur_transforms_.scale = 1 / std::abs(scale);
  } else if (scale > 0) {
    handled_scale = scale / cur_transforms_.scale;
    cur_transforms_.scale = scale;
  }

  scale = handled_scale;
}

void TransformationHandler::HandleOffsets(double &x_offset, double &y_offset,
                                          double &z_offset) {
  double handled_offset = x_offset - cur_transforms_.x_offset;
  cur_transforms_.x_offset = x_offset;
  x_offset = handled_offset;

  handled_offset = y_offset - cur_transforms_.y_offset;
  cur_transforms_.y_offset = y_offset;
  y_offset = handled_offset;

  handled_offset = z_offset - cur_transforms_.z_offset;
  cur_transforms_.z_offset = z_offset;
  z_offset = handled_offset;
}

void TransformationHandler::HandleRotationAngles(double &x_angle,
                                                 double &y_angle,
                                                 double &z_angle) {
  double handled_angle = x_angle - cur_transforms_.x_angle;
  cur_transforms_.x_angle = x_angle;
  x_angle = handled_angle;

  handled_angle = y_angle - cur_transforms_.y_angle;
  cur_transforms_.y_angle = y_angle;
  y_angle = handled_angle;

  handled_angle = z_angle - cur_transforms_.z_angle;
  cur_transforms_.z_angle = z_angle;
  z_angle = handled_angle;
}

}  // namespace s21
