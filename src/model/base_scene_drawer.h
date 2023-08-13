#ifndef MODEL_BASE_SCENE_DRAWER_H
#define MODEL_BASE_SCENE_DRAWER_H

#include "scene.h"

namespace s21 {
class BaseSceneDrawer {
 public:
  virtual void DrawScene(const Scene& scene) = 0;
};
}  // namespace s21

#endif  // MODEL_BASE_SCENE_DRAWER_H
