#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      ctrl_(Controller::GetInstance()) {
  setlocale(LC_NUMERIC, "C");
  ui_->setupUi(this);
  InitVisualSettingsWidgets();
}

MainWindow::~MainWindow() {
  setlocale(LC_NUMERIC, NULL);
  delete ui_;
}

void MainWindow::on_btnLoadModel_clicked() {
  std::string filter = "Model file (*.obj)";
  std::string path =
      QFileInfo(QFileDialog::getOpenFileName(this, "Загрузка модели", ".",
                                             QString::fromUtf8(filter.c_str())))
          .absoluteFilePath()
          .toStdString();
  if (!path.empty()) {
    int extreme_coordinate = ui_->oglwidget->height() < ui_->oglwidget->width()
                                 ? ui_->oglwidget->height() / 1.9
                                 : ui_->oglwidget->width() / 1.9;
    FacadeOperationResult operation_result = ctrl_.LoadScene(
        path, NormalizationParameters(-extreme_coordinate, extreme_coordinate));
    if (!operation_result.IsSuccess()) {
      QMessageBox::warning(
          this, "Ошибка",
          QString::fromStdString(operation_result.GetErrorMessage()));
    } else {
      operation_result = ctrl_.DrawScene();
      if (!operation_result.IsSuccess()) {
        QMessageBox::warning(
            this, "Ошибка",
            QString::fromStdString(operation_result.GetErrorMessage()));
      } else {
        ui_->oglwidget->update();
        ui_->lbModelPath->setText(QString::fromStdString(path));
        ui_->lbVerticesCount->setText(
            QString::number(ctrl_.GetVerticesCount()));
        ui_->lbFacetsCount->setText(QString::number(ctrl_.GetEdgesCount()));
        ResetTransformationWidgets();
      }
    }
  }
}

void MainWindow::on_btnScreeshot_clicked() {
  std::string ext = ui_->rbJPEG->isChecked() ? ".jpeg" : ".bmp";
  std::string filter = "Image file (*" + ext + ")";
  QString filename = QFileDialog::getSaveFileName(
      this, "Сохранить снимок", ".", QString::fromUtf8(filter.c_str()));
  if (!filename.isEmpty()) {
    ui_->oglwidget->grab().save(filename);
  }
}

void MainWindow::on_btnRecordGif_clicked() {
  QMessageBox::StandardButton choice =
      QMessageBox::information(this, "Запись GIF",
                               "Проведенные в течение следующих 5 секунд  "
                               "трансформации над моделью будут записаны",
                               QMessageBox::Ok, QMessageBox::Cancel);
  if (choice == QMessageBox::Ok) {
    DisableWidgetsBeforeGifRecord();
    ctrl_.EnableGifRecording();
    connect(ctrl_.GetGifRecordingTimer(), SIGNAL(timeout()),
            SLOT(onTimerAlarm()));
  }
}

void MainWindow::onTimerAlarm() {
  ctrl_.StopGifRecordingTimer();
  QMessageBox::StandardButton choice =
      QMessageBox::information(this, "", "Запись завершена. Сохранить?",
                               QMessageBox::Ok, QMessageBox::Cancel);
  if (choice == QMessageBox::Ok) {
    std::string filter = "GIF file (*.gif)";
    QString filename = QFileDialog::getSaveFileName(
        this, "Сохранить gif", ".", QString::fromUtf8(filter.c_str()));
    if (!filename.isEmpty()) {
      ctrl_.SaveGif(filename);
    }
  }

  ctrl_.DisableGifRecording();
  EnableWidgetsAfterGifRecord();
}

void MainWindow::on_btnLineColor_clicked() {
  QColor line_color = QColorDialog::getColor(Qt::white, this, "Цвет линий",
                                             QColorDialog::ShowAlphaChannel);
  if (line_color.isValid()) {
    ctrl_.UpdateColorSetting(ColorConsumer::kLine, line_color);
    ui_->oglwidget->update();
  }
}

void MainWindow::on_btnVertexColor_clicked() {
  QColor vertex_color = QColorDialog::getColor(Qt::white, this, "Цвет вершин",
                                               QColorDialog::ShowAlphaChannel);
  if (vertex_color.isValid()) {
    ctrl_.UpdateColorSetting(ColorConsumer::kVertex, vertex_color);
    ui_->oglwidget->update();
  }
}

void MainWindow::on_btnBackgroundColor_clicked() {
  QColor bgcolor = QColorDialog::getColor(Qt::white, this, "Цвет фона",
                                          QColorDialog::ShowAlphaChannel);
  if (bgcolor.isValid()) {
    ctrl_.UpdateColorSetting(ColorConsumer::kBackground, bgcolor);
    ui_->oglwidget->update();
  }
}

void MainWindow::on_rbSolidLineType_clicked(bool checked) {
  if (checked) ctrl_.UpdateDisplayTypeSetting(kSolidLine);
  ui_->oglwidget->update();
}

void MainWindow::on_rbDashedLineType_clicked(bool checked) {
  if (checked) ctrl_.UpdateDisplayTypeSetting(kDashLine);
  ui_->oglwidget->update();
}

void MainWindow::on_hslLineThickness_valueChanged(int value) {
  ui_->sbLineThickness->setValue(value);
}

void MainWindow::on_sbLineThickness_valueChanged(int arg1) {
  ui_->hslLineThickness->setValue(arg1);
  ctrl_.UpdateSizeSetting(SizeConsumer::kLine, arg1);
  ui_->oglwidget->update();
}

void MainWindow::on_rbNoneVerticesType_clicked(bool checked) {
  if (checked) ctrl_.UpdateDisplayTypeSetting(kNoneVertex);
  ui_->oglwidget->update();
}

void MainWindow::on_rbCircleVerticesType_clicked(bool checked) {
  if (checked) ctrl_.UpdateDisplayTypeSetting(kCircleVertex);
  ui_->oglwidget->update();
}

void MainWindow::on_rbSquareVerticesType_clicked(bool checked) {
  if (checked) ctrl_.UpdateDisplayTypeSetting(kSquareVertex);
  ui_->oglwidget->update();
}

void MainWindow::on_hslVerticesSize_valueChanged(int value) {
  ui_->sbVerticesSize->setValue(value);
}

void MainWindow::on_sbVerticesSize_valueChanged(int arg1) {
  ui_->hslVerticesSize->setValue(arg1);
  ctrl_.UpdateSizeSetting(SizeConsumer::kVertex, arg1);
  ui_->oglwidget->update();
}

void MainWindow::on_rbParallelProjection_clicked(bool checked) {
  if (checked) ctrl_.UpdateDisplayTypeSetting(kParallelProjection);
  ui_->oglwidget->update();
}

void MainWindow::on_rbCentralProjection_clicked(bool checked) {
  if (checked) ctrl_.UpdateDisplayTypeSetting(kCentralProjection);
  ui_->oglwidget->update();
}

void MainWindow::on_dsbScale_valueChanged(double arg1) {
  arg1 = round(arg1 * 10) / 10;
  if (arg1 == 0.9) {
    ui_->dsbScale->setValue(-1.1);
  } else if (arg1 == -0.9 || arg1 == 0) {
    ui_->dsbScale->setValue(1.0);
  }
}

void MainWindow::on_dsbScale_editingFinished() {
  double value = round(ui_->dsbScale->value() * 10) / 10;

  if (value > 0) {
    value = value * 10 - 10;
  } else if (value < 0) {
    value = value * 10 + 10;
  }

  ui_->hslScale->setValue(value);
  ui_->hslScale->sliderMoved(value);
}

void MainWindow::on_hslScale_sliderMoved(int position) {
  if (position >= 0) {
    ui_->dsbScale->setValue((position + 10) / 10.0);
  } else {
    ui_->dsbScale->setValue((position - 10) / 10.0);
  }

  ctrl_.ScaleScene(ui_->dsbScale->value());
  ui_->oglwidget->update();
}

void MainWindow::on_dsbMoveX_editingFinished() {
  ui_->hslMoveX->setValue(ui_->dsbMoveX->value() * 10);
  ui_->hslMoveX->sliderMoved(ui_->dsbMoveX->value() * 10);
}

void MainWindow::on_hslMoveX_sliderMoved(int position) {
  ui_->dsbMoveX->setValue(position / 10.0);
  ctrl_.MoveScene(ui_->dsbMoveX->value(), ui_->dsbMoveY->value(),
                  ui_->dsbMoveZ->value());
  ui_->oglwidget->update();
}

void MainWindow::on_dsbMoveY_editingFinished() {
  ui_->hslMoveY->setValue(ui_->dsbMoveY->value() * 10);
  ui_->hslMoveY->sliderMoved(ui_->dsbMoveY->value() * 10);
}

void MainWindow::on_hslMoveY_sliderMoved(int position) {
  ui_->dsbMoveY->setValue(position / 10.0);
  ctrl_.MoveScene(ui_->dsbMoveX->value(), ui_->dsbMoveY->value(),
                  ui_->dsbMoveZ->value());
  ui_->oglwidget->update();
}

void MainWindow::on_dsbMoveZ_editingFinished() {
  ui_->hslMoveZ->setValue(ui_->dsbMoveZ->value() * 10);
  ui_->hslMoveZ->sliderMoved(ui_->dsbMoveZ->value() * 10);
}

void MainWindow::on_hslMoveZ_sliderMoved(int position) {
  ui_->dsbMoveZ->setValue(position / 10.0);
  ctrl_.MoveScene(ui_->dsbMoveX->value(), ui_->dsbMoveY->value(),
                  ui_->dsbMoveZ->value());
  ui_->oglwidget->update();
}

void MainWindow::on_sbRotateX_editingFinished() {
  ui_->hslRotateX->setValue(ui_->sbRotateX->value());
  ui_->hslRotateX->sliderMoved(ui_->sbRotateX->value());
}

void MainWindow::on_hslRotateX_sliderMoved(int position) {
  ui_->sbRotateX->setValue(position);
  ctrl_.RotateScene(ui_->sbRotateX->value(), ui_->sbRotateY->value(),
                    ui_->sbRotateZ->value());
  ui_->oglwidget->update();
}

void MainWindow::on_sbRotateY_editingFinished() {
  ui_->hslRotateY->setValue(ui_->sbRotateY->value());
  ui_->hslRotateY->sliderMoved(ui_->sbRotateY->value());
}

void MainWindow::on_hslRotateY_sliderMoved(int position) {
  ui_->sbRotateY->setValue(position);
  ctrl_.RotateScene(ui_->sbRotateX->value(), ui_->sbRotateY->value(),
                    ui_->sbRotateZ->value());
  ui_->oglwidget->update();
}

void MainWindow::on_sbRotateZ_editingFinished() {
  ui_->hslRotateZ->setValue(ui_->sbRotateZ->value());
  ui_->hslRotateZ->sliderMoved(ui_->sbRotateZ->value());
}

void MainWindow::on_hslRotateZ_sliderMoved(int position) {
  ui_->sbRotateZ->setValue(position);
  ctrl_.RotateScene(ui_->sbRotateX->value(), ui_->sbRotateY->value(),
                    ui_->sbRotateZ->value());
  ui_->oglwidget->update();
}

void MainWindow::ResetTransformationWidgets() {
  ui_->dsbScale->setValue(1);
  ui_->dsbMoveX->setValue(0);
  ui_->hslMoveX->setValue(0);
  ui_->dsbMoveY->setValue(0);
  ui_->hslMoveY->setValue(0);
  ui_->dsbMoveZ->setValue(0);
  ui_->hslMoveZ->setValue(0);
  ui_->sbRotateX->setValue(0);
  ui_->hslRotateX->setValue(0);
  ui_->sbRotateY->setValue(0);
  ui_->hslRotateY->setValue(0);
  ui_->sbRotateZ->setValue(0);
  ui_->hslRotateZ->setValue(0);
}

void MainWindow::InitVisualSettingsWidgets() {
  const Settings settings = ctrl_.GetStateRef();

  switch (settings.type.projection) {
    case kCentral:
      ui_->rbCentralProjection->setChecked(true);
      break;
    case kParallel:
      ui_->rbParallelProjection->setChecked(true);
      break;
  }

  ui_->sbVerticesSize->setValue(settings.size.vertex_size);
  switch (settings.type.vertex) {
    case kCircle:
      ui_->rbCircleVerticesType->setChecked(true);
      break;
    case kSquare:
      ui_->rbSquareVerticesType->setChecked(true);
      break;
    case kNone:
      ui_->rbNoneVerticesType->setChecked(true);
      break;
  }

  ui_->sbLineThickness->setValue(settings.size.line_size);
  switch (settings.type.line) {
    case kDash:
      ui_->rbDashedLineType->setChecked(true);
      break;
    case kSolid:
      ui_->rbSolidLineType->setChecked(true);
      break;
  }
}

void MainWindow::DisableWidgetsBeforeGifRecord() {
  ui_->btnBackgroundColor->setDisabled(true);
  ui_->btnLineColor->setDisabled(true);
  ui_->btnVertexColor->setDisabled(true);
  ui_->btnLoadModel->setDisabled(true);
  ui_->btnScreeshot->setDisabled(true);
  ui_->btnRecordGif->setDisabled(true);
  ui_->rbDashedLineType->setDisabled(true);
  ui_->rbSolidLineType->setDisabled(true);
  ui_->hslLineThickness->setDisabled(true);
  ui_->sbLineThickness->setDisabled(true);
  ui_->rbNoneVerticesType->setDisabled(true);
  ui_->rbCircleVerticesType->setDisabled(true);
  ui_->rbSquareVerticesType->setDisabled(true);
  ui_->hslVerticesSize->setDisabled(true);
  ui_->sbVerticesSize->setDisabled(true);
  ui_->rbCentralProjection->setDisabled(true);
  ui_->rbParallelProjection->setDisabled(true);
}

void MainWindow::EnableWidgetsAfterGifRecord() {
  ui_->btnBackgroundColor->setDisabled(false);
  ui_->btnLineColor->setDisabled(false);
  ui_->btnVertexColor->setDisabled(false);
  ui_->btnLoadModel->setDisabled(false);
  ui_->btnScreeshot->setDisabled(false);
  ui_->btnRecordGif->setDisabled(false);
  ui_->rbDashedLineType->setDisabled(false);
  ui_->rbSolidLineType->setDisabled(false);
  ui_->hslLineThickness->setDisabled(false);
  ui_->sbLineThickness->setDisabled(false);
  ui_->rbNoneVerticesType->setDisabled(false);
  ui_->rbCircleVerticesType->setDisabled(false);
  ui_->rbSquareVerticesType->setDisabled(false);
  ui_->hslVerticesSize->setDisabled(false);
  ui_->sbVerticesSize->setDisabled(false);
  ui_->rbCentralProjection->setDisabled(false);
  ui_->rbParallelProjection->setDisabled(false);
}

}  // namespace s21
