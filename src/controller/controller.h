#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include "../model/facade.h"
#include "../model/settings.h"

namespace s21 {
class Controller {
 public:
  static Controller& GetInstance() {
    static Controller instance;
    return instance;
  }

  FacadeOperationResult LoadScene(const std::string& path,
                                  NormalizationParameters norm_params) const {
    return facade_.LoadScene(path, norm_params);
  }

  FacadeOperationResult DrawScene() const { return facade_.DrawScene(); }

  void MoveScene(double x_offset, double y_offset, double z_offset) {
    facade_.MoveScene(x_offset, y_offset, z_offset);
  }

  void RotateScene(int x_angle, int y_angle, int z_angle) {
    facade_.RotateScene(x_angle, y_angle, z_angle);
  }

  void ScaleScene(double factor) { facade_.ScaleScene(factor); }

  size_t GetVerticesCount() const { return facade_.GetVerticesCount(); }

  size_t GetEdgesCount() const { return facade_.GetEdgesCount(); }

  const vector<unsigned int>* GetIndicesRef() const {
    return facade_.GetIndicesRef();
  }

  const vector<double>* GetCoordinatesRef() const {
    return facade_.GetCoordinatesRef();
  }

  const Settings& GetStateRef() const { return facade_.GetStateRef(); }

  void UpdateColorSetting(ColorConsumer consumer, QColor color) {
    facade_.UpdateColorSetting(consumer, color);
  }

  void UpdateDisplayTypeSetting(DisplayType type) {
    facade_.UpdateDisplayTypeSetting(type);
  }

  void UpdateSizeSetting(SizeConsumer consumer, unsigned int size) {
    facade_.UpdateSizeSetting(consumer, size);
  }

  bool GifRecordingEnabled() const { return facade_.GifRecordingEnabled(); }
  void EnableGifRecording() { facade_.EnableGifRecording(); }
  void DisableGifRecording() { facade_.DisableGifRecording(); }
  void SaveGif(const QString& fileName) { facade_.SaveGif(fileName); }
  void AddFrame(const QImage& image) { facade_.AddFrame(image); }
  const QTimer* GetGifRecordingTimer() const {
    return facade_.GetGifRecordingTimer();
  }
  void StopGifRecordingTimer() { facade_.StopGifRecordingTimer(); }

 protected:
  Controller() : facade_(Facade::GetInstance()) {}
  Controller(const Controller&) : Controller() {}
  void operator=(const Controller&) {}

 private:
  Facade& facade_;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H
