#include "qt_scene_drawer.h"

namespace s21 {
const vector<unsigned int>* QtSceneDrawer::GetIndexesRef() const {
  return &indexes_;
}
const vector<double>* QtSceneDrawer::GetCoordinatesRef() const {
  return &coordinates_;
}

void QtSceneDrawer::SetIndexes(const Scene& scene) {
  indexes_.clear();
  for (auto& figure : scene.GetFigures()) {
    for (auto& edge : figure.GetEdges()) {
      indexes_.push_back(edge.GetBeginVertex());
      indexes_.push_back(edge.GetEndVertex());
    }
  }
}

void QtSceneDrawer::SetCoordinates(const Scene& scene) {
  coordinates_.clear();
  for (auto& figure : scene.GetFigures()) {
    for (auto& item : figure.GetVertices()) {
      coordinates_.push_back(item.GetPosition().x);
      coordinates_.push_back(item.GetPosition().y);
      coordinates_.push_back(item.GetPosition().z);
    }
  }
}

void QtSceneDrawer::DrawScene(const Scene& scene) {
  SetIndexes(scene);
  SetCoordinates(scene);
}

}  // namespace s21
