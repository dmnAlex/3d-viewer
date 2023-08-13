#ifndef MODEL_FACADE_H
#define MODEL_FACADE_H

#include "base_file_reader.h"
#include "base_scene_drawer.h"
#include "facade_operation_result.h"
#include "file_reader.h"
#include "qt_gif_maker.h"
#include "qt_scene_drawer.h"
#include "scene.h"
#include "settings_store.h"
#include "transform_matrix.h"
#include "transform_matrix_builder.h"
#include "transformation_handler.h"

namespace s21 {
class Facade {
 public:
  static Facade& GetInstance() {
    static Facade instance;
    return instance;
  }

  FacadeOperationResult DrawScene();
  FacadeOperationResult LoadScene(const std::string& path,
                                  NormalizationParameters norm_params);
  void MoveScene(double x_offset, double y_offset, double z_offset);
  void RotateScene(double x, double y, double z);
  void ScaleScene(double new_factor);

  size_t GetVerticesCount() { return scene_.GetVerticesCount(); }
  size_t GetEdgesCount() { return scene_.GetEdgesCount(); }

  const vector<unsigned int>* GetIndicesRef() const;
  const vector<double>* GetCoordinatesRef() const;
  const Settings& GetStateRef() const;

  void UpdateColorSetting(ColorConsumer consumer, QColor color) {
    settings_store_.UpdateColorSetting(consumer, color);
  }

  void UpdateDisplayTypeSetting(DisplayType type) {
    settings_store_.UpdateDisplayTypeSetting(type);
  }

  void UpdateSizeSetting(SizeConsumer consumer, unsigned int size) {
    settings_store_.UpdateSizeSetting(consumer, size);
  }

  bool GifRecordingEnabled() const { return gif_maker_.IsEnabled(); }
  void EnableGifRecording() { gif_maker_.Enable(); }
  void DisableGifRecording() { gif_maker_.Disable(); }
  void SaveGif(const QString& fileName) { gif_maker_.Save(fileName); }
  void AddFrame(const QImage& image) { return gif_maker_.AddFrame(image); }
  const QTimer* GetGifRecordingTimer() const { return gif_maker_.GetTimer(); }
  void StopGifRecordingTimer() { gif_maker_.StopTimer(); }

 protected:
  Facade()
      : file_reader_(FileReader::GetInstance()),
        scene_drawer_(QtSceneDrawer::GetInstance()),
        settings_store_(SettingsStore("settings.cfg")) {}
  Facade(const Facade&) : Facade() {}
  void operator=(const Facade&) {}

 private:
  FileReader& file_reader_;
  QtSceneDrawer& scene_drawer_;
  SettingsStore settings_store_;
  Scene scene_;
  TransformationHandler transform_handler_;
  QtGifMaker gif_maker_;
};
}  // namespace s21

#endif  // MODEL_FACADE_H
