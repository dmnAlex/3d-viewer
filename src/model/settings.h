#ifndef MODEL_SETTINGS_H
#define MODEL_SETTINGS_H

#include <QColor>

namespace s21 {
enum DisplayType {
  kParallelProjection,
  kCentralProjection,
  kSolidLine,
  kDashLine,
  kNoneVertex,
  kCircleVertex,
  kSquareVertex
};

enum ProjectionType { kParallel, kCentral };
enum VertexType { kNone, kCircle, kSquare };
enum LineType { kSolid, kDash };
enum class ColorConsumer { kBackground, kVertex, kLine };
enum class SizeConsumer { kVertex, kLine };

struct ColorSettings {
  QColor background = Qt::white;
  QColor vertex = Qt::black;
  QColor line = Qt::black;
};

struct TypeSettings {
  ProjectionType projection = kParallel;
  VertexType vertex = kNone;
  LineType line = kSolid;
};

struct SizeSettings {
  unsigned int vertex_size = 1;
  unsigned int line_size = 1;
};

struct Settings {
  ColorSettings color;
  TypeSettings type;
  SizeSettings size;
};

}  // namespace s21

#endif  // MODEL_SETTINGS_H
