#ifndef MODEL_FIGURE_H
#define MODEL_FIGURE_H

#include "edge.h"
#include "transform_matrix.h"
#include "vertex.h"

namespace s21 {
class Figure {
 public:
  Figure() {}
  Figure(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges)
      : vertices_(vertices), edges_(edges) {}

  const std::vector<Vertex>& GetVertices() const { return vertices_; }
  void AddVertex(const Vertex& vertex) { vertices_.push_back(vertex); }
  Vertex& VertexAt(size_t index) { return vertices_.at(index); }

  const std::vector<Edge>& GetEdges() const { return edges_; }
  void AddEdge(Edge edge) { edges_.push_back(edge); }
  Edge& EdgeAt(size_t index) { return edges_.at(index); }

  size_t GetVerticesCount() const { return vertices_.size(); }
  size_t GetEdgesCount() const { return edges_.size(); }

  void Transform(TransformMatrix& matrix) {
    for (auto& vertex : vertices_) {
      vertex.Transform(matrix);
    }
  }

  void Clear() {
    vertices_.clear();
    edges_.clear();
  }

 private:
  std::vector<Vertex> vertices_;
  std::vector<Edge> edges_;
};
}  // namespace s21

#endif  // MODEL_FIGURE_H
