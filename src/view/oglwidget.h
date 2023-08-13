#ifndef VIEW_OGLWIDGET_H
#define VIEW_OGLWIDGET_H

#include <QOpenGLWidget>

#include "../controller/controller.h"

namespace s21 {
class OGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  OGLWidget(QWidget* parent = nullptr);

 public:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  Controller& ctrl_;
  const vector<unsigned int>* indices_;
  const vector<double>* coordinates_;
  const Settings& settings_;
};

}  // namespace s21

#endif  // VIEW_OGLWIDGET_H
