#ifndef MODEL_NORMALIZATION_PARAMETES_H
#define MODEL_NORMALIZATION_PARAMETES_H

namespace s21 {
struct NormalizationParameters {
  NormalizationParameters(double min, double max)
      : min_coord(min), max_coord(max) {}

  double min_coord;
  double max_coord;
};
}  // namespace s21

#endif  // MODEL_NORMALIZATION_PARAMETES_H
