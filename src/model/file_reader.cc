#include "file_reader.h"

namespace s21 {
Scene FileReader::ReadScene(const std::string& path) {
  Scene scene;
  std::ifstream ifs(path);
  if (ifs.is_open()) {
    Figure figure;
    std::string line;
    bool is_correct_file = true;
    while (is_correct_file && std::getline(ifs, line)) {
      if (*line.data() == 'v' && *(line.data() + 1) == ' ') {
        is_correct_file = ReadVertexLine(line, figure);
      } else if (*line.data() == 'f' && *(line.data() + 1) == ' ') {
        is_correct_file = ReadFaceLine(line, figure);
      }
    }

    if (is_correct_file && !figure.GetVertices().empty() &&
        !figure.GetEdges().empty()) {
      scene.AddFigure(figure);
    } else {
      figure.Clear();
    }
  }

  ifs.close();
  return scene;
}

bool FileReader::ReadVertexLine(const std::string& line, Figure& figure) {
  bool is_correct_file = true;
  double coordinates[3];
  const char* line_data = static_cast<const char*>(line.data() + 1);
  char* end_ptr = nullptr;
  int i = 0;
  for (; !is_line_end(line_data); ++i) {
    if (i >= kVertexCoordinatesMaxCount) {
      is_correct_file = false;  // line contains more then 3 coordinates
      break;
    }

    coordinates[i] = std::strtod(line_data, &end_ptr);
    if (!std::isfinite(coordinates[i]) || line_data == end_ptr) {
      is_correct_file = false;  // all other mistakes
      break;
    }

    line_data = end_ptr;
  }

  if (i < kVertexCoordinatesMaxCount) {
    is_correct_file = false;  // line contains less then 3 coordinates
  }

  if (is_correct_file) {
    figure.AddVertex(Point3D(coordinates[0], coordinates[1], coordinates[2]));
  }

  return is_correct_file;
}

bool FileReader::ReadFaceLine(const std::string& line, Figure& figure) {
  bool is_correct_file = true;
  size_t element_begin = line.find_first_not_of(' ', 1);
  if (element_begin == std::variant_npos) {
    is_correct_file = false;  // line doesn't have elements
  } else {
    int elements_count = 0;
    while (element_begin != std::variant_npos) {
      size_t element_end = line.find_first_of(' ', element_begin);
      if (element_end == std::variant_npos) {  // reached line's end
        element_end = line.size();
      }

      FaceElement face_element;
      if (!ReadFaceLineElement(
              line.substr(element_begin, element_end - element_begin),
              face_element)) {
        is_correct_file = false;  // incorrect faceline element
        break;
      }

      if (figure.GetVerticesCount() <
          static_cast<size_t>(abs(face_element.vertex_index))) {
        is_correct_file = false;  // vertex index out of range
        break;
      }

      int position =
          face_element.vertex_index > 0
              ? face_element.vertex_index - 1
              : (face_element.vertex_index + figure.GetVertices().size()) %
                    figure.GetVertices().size();
      if (elements_count > 0) {
        figure.EdgeAt(figure.GetEdgesCount() - 1).SetEndVertex(position);
      }

      ++elements_count;

      if (element_end != line.size()) {
        element_begin = line.find_first_not_of(' ', element_end);
        figure.AddEdge(Edge(position, position));
      } else {
        element_begin = std::variant_npos;
        is_correct_file =
            elements_count >= kPolygonMinSize;  // too few elements if false
      }
    }
  }

  return is_correct_file;
}

bool FileReader::ReadFaceLineElement(const std::string& str,
                                     FaceElement& face_element) {
  bool is_correct_file = true;
  if (!std::isdigit(str.front()) && *str.data() != '-') {
    is_correct_file = false;  // incorrect faceline element
  } else {
    const char* str_data = static_cast<const char*>(str.data());
    char* end_ptr = nullptr;
    for (int index_number = 1; !is_line_end(str_data); ++index_number) {
      if (index_number > 3) {
        is_correct_file = false;  // more then 3 indices in the faceline element
        break;
      }

      long index = std::strtol(str_data, &end_ptr, 10);
      if (index > INT_MAX || index < INT_MIN ||
          (*end_ptr != '/' && *end_ptr != ' ' && !is_line_end(end_ptr))) {
        is_correct_file = false;  // incorrect element
        break;
      }

      switch (index_number) {
        case 1:
          face_element.vertex_index = index;
          break;
        case 2:
          face_element.texture_index = index;
          break;
        case 3:
          face_element.normal_index = index;
          break;
      }

      str_data = is_line_end(end_ptr) ? end_ptr : end_ptr + 1;
    }
  }

  return is_correct_file;
}

}  // namespace s21
