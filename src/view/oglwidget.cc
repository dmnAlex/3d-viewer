#include "oglwidget.h"

#include <QApplication>

namespace s21 {
OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      ctrl_(Controller::GetInstance()),
      indices_(ctrl_.GetIndicesRef()),
      coordinates_(ctrl_.GetCoordinatesRef()),
      settings_(ctrl_.GetStateRef()) {}

void OGLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glLineStipple(1, 0x0333);
}

void OGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OGLWidget::paintGL() {
  // background settings
  glClearColor(
      settings_.color.background.redF(), settings_.color.background.greenF(),
      settings_.color.background.blueF(), settings_.color.background.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // projection settings
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double depth = width() > height() ? width() : height();

  if (settings_.type.projection == kCentral) {
    glFrustum(-width(), width(), -height(), height(), depth / 2, depth * 4);
  } else {
    glOrtho(-width(), width(), -height(), height(), 1, depth * 2);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -depth);

  glVertexPointer(3, GL_DOUBLE, 0, coordinates_->data());
  glEnableClientState(GL_VERTEX_ARRAY);

  // lines settings
  glLineWidth(settings_.size.line_size);
  glColor3d(settings_.color.line.redF(), settings_.color.line.greenF(),
            settings_.color.line.blueF());
  if (settings_.type.line == kDash) glEnable(GL_LINE_STIPPLE);

  // drawing lines
  glDrawElements(GL_LINES, indices_->size(), GL_UNSIGNED_INT, indices_->data());

  // vertices settings
  glPointSize(settings_.size.vertex_size);
  glColor3d(settings_.color.vertex.redF(), settings_.color.vertex.greenF(),
            settings_.color.vertex.blueF());
  if (settings_.type.vertex == kCircle) glEnable(GL_POINT_SMOOTH);

  // drawing vertices
  if (settings_.type.vertex != kNone)
    glDrawArrays(GL_POINTS, 0, coordinates_->size() / 3);

  // disabling
  glDisable(GL_LINE_STIPPLE);
  glDisable(GL_POINT_SMOOTH);
  glDisableClientState(GL_VERTEX_ARRAY);

  if (ctrl_.GifRecordingEnabled()) {
    ctrl_.AddFrame(grabFramebuffer().scaled(640, 480, Qt::IgnoreAspectRatio,
                                            Qt::SmoothTransformation));
  }
}
}  // namespace s21
