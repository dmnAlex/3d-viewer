#ifndef MODEL_EDGE_H
#define MODEL_EDGE_H

#include <cstddef>
namespace s21 {
class Edge {
 public:
  Edge(unsigned int begin, unsigned int end)
      : begin_vertex_(begin), end_vertex_(end) {}

  unsigned int GetBeginVertex() const { return begin_vertex_; }
  void SetBeginVertex(unsigned int begin) { begin_vertex_ = begin; }

  unsigned int GetEndVertex() const { return end_vertex_; }
  void SetEndVertex(unsigned int end) { end_vertex_ = end; }

 private:
  unsigned int begin_vertex_;
  unsigned int end_vertex_;
};
}  // namespace s21

#endif  // MODEL_EDGE_H
