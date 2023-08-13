#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>

#include "../controller/controller.h"
#include "../../libs/gifimagelib/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_btnLoadModel_clicked();
  void on_btnScreeshot_clicked();
  void on_btnRecordGif_clicked();

  void on_btnLineColor_clicked();
  void on_btnVertexColor_clicked();
  void on_btnBackgroundColor_clicked();

  void on_rbSolidLineType_clicked(bool checked);
  void on_rbDashedLineType_clicked(bool checked);
  void on_hslLineThickness_valueChanged(int value);
  void on_sbLineThickness_valueChanged(int arg1);

  void on_rbNoneVerticesType_clicked(bool checked);
  void on_rbCircleVerticesType_clicked(bool checked);
  void on_rbSquareVerticesType_clicked(bool checked);
  void on_hslVerticesSize_valueChanged(int value);
  void on_sbVerticesSize_valueChanged(int arg1);

  void on_rbParallelProjection_clicked(bool checked);
  void on_rbCentralProjection_clicked(bool checked);

  void on_dsbScale_valueChanged(double arg1);
  void on_dsbScale_editingFinished();
  void on_hslScale_sliderMoved(int position);
  void on_dsbMoveX_editingFinished();
  void on_hslMoveX_sliderMoved(int position);
  void on_dsbMoveY_editingFinished();
  void on_hslMoveY_sliderMoved(int position);
  void on_dsbMoveZ_editingFinished();
  void on_hslMoveZ_sliderMoved(int position);
  void on_sbRotateX_editingFinished();
  void on_hslRotateX_sliderMoved(int position);
  void on_sbRotateY_editingFinished();
  void on_hslRotateY_sliderMoved(int position);
  void on_sbRotateZ_editingFinished();
  void on_hslRotateZ_sliderMoved(int position);

  void onTimerAlarm();

 private:
  void ResetTransformationWidgets();
  void InitVisualSettingsWidgets();
  void DisableWidgetsBeforeGifRecord();
  void EnableWidgetsAfterGifRecord();

  Ui::MainWindow* ui_;
  Controller& ctrl_;
};
}  // namespace s21
#endif  // VIEW_MAINWINDOW_H
