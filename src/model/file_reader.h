#ifndef MODEL_FILE_READER_H
#define MODEL_FILE_READER_H

#include <climits>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <variant>

#include "base_file_reader.h"
#include "face_element.h"

namespace s21 {
class FileReader : BaseFileReader {
 public:
  static FileReader& GetInstance() {
    static FileReader instance;
    return instance;
  }

  virtual Scene ReadScene(const std::string& path) override;

 protected:
  FileReader() {}
  FileReader(const FileReader&) {}
  void operator=(const FileReader&) {}

 private:
  const int kVertexCoordinatesMaxCount = 3;
  const int kPolygonMinSize = 3;

  bool ReadVertexLine(const std::string& line, Figure& figure);
  bool ReadFaceLine(const std::string& line, Figure& figure);
  bool ReadFaceLineElement(const std::string& str, FaceElement& face_element);
  static bool is_line_end(const char* ptr) {
    return *ptr == '\r' || *ptr == '\n' || *ptr == '\0';
  }
};

}  // namespace s21

#endif  // MODEL_FILE_READER_H
