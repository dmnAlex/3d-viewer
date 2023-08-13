#ifndef MODEL_QT_SCENE_DRAWER_H
#define MODEL_QT_SCENE_DRAWER_H

#include "base_scene_drawer.h"
#include "figure.h"
#include "point_3d.h"
#include "scene.h"

using std::vector;

namespace s21 {
class QtSceneDrawer : public BaseSceneDrawer {
 public:
  static QtSceneDrawer& GetInstance() {
    static QtSceneDrawer instance;
    return instance;
  }

  const vector<unsigned int>* GetIndexesRef() const;
  const vector<double>* GetCoordinatesRef() const;
  void SetIndexes(const Scene& scene);
  void SetCoordinates(const Scene& scene);
  virtual void DrawScene(const Scene& scene) override;

 protected:
  QtSceneDrawer() {}
  QtSceneDrawer(const QtSceneDrawer&) {}
  void operator=(const QtSceneDrawer&) {}

 private:
  vector<unsigned int> indexes_;
  vector<double> coordinates_;
};
}  // namespace s21

#endif  // MODEL_QT_SCENE_DRAWER_H
