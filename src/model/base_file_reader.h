#ifndef MODEL_BASE_FILE_READER_H
#define MODEL_BASE_FILE_READER_H

#include <string>

#include "scene.h"

namespace s21 {
class BaseFileReader {
 public:
  virtual Scene ReadScene(const std::string& path) = 0;
};
}  // namespace s21

#endif  // MODEL_BASE_FILE_READER_H
