#ifndef QTGIFMAKER_H
#define QTGIFMAKER_H

#include "../../libs/gifimagelib/gifimage/qgifimage.h"

#include <QSize>
#include <QTimer>

namespace s21 {
class QtGifMaker {
 public:
  void AddFrame(const QImage& image) { gif_->addFrame(image); }
  void Save(const QString& fileName) {
    if (gif_->frameCount() > 50) {
      gif_->setDefaultDelay(kDefaultDelay / (gif_->frameCount() / 50.0));
    }
    gif_->save(fileName);
  }

  bool IsEnabled() const { return gif_ != nullptr; }
  void Enable() {
    gif_ = new QGifImage(QSize(640, 480));
    gif_->setDefaultDelay(kDefaultDelay);
    StartTimer();
  }

  void Disable() {
    delete gif_;
    gif_ = nullptr;
  }

  const QTimer* GetTimer() const { return timer_; }
  void StartTimer() {
    timer_ = new QTimer();
    timer_->start(kRecordTime);
  };
  void StopTimer() {
    timer_->stop();
    delete timer_;
    timer_ = nullptr;
  }

 private:
  const int kRecordTime = 5000;
  const int kDefaultDelay = 100;

  QGifImage* gif_ = nullptr;
  QTimer* timer_ = nullptr;
};
}  // namespace s21

#endif  // QTGIFMAKER_H
