#include "facade.h"

namespace s21 {
FacadeOperationResult Facade::LoadScene(const std::string& path,
                                        NormalizationParameters norm_params) {
  FacadeOperationResult operation_result;
  Scene scene = file_reader_.ReadScene(path);
  if (scene.GetFigures().empty()) {
    operation_result.SetErrorMessage(
        "Файл некорректен или у вас недостаточно прав для его чтения");
    operation_result.SetIsSucces(false);
  } else {
    scene_ = scene;
    scene_.NormalizeCoordinates(norm_params);
    transform_handler_.ResetTransformations();
  }

  return operation_result;
}

FacadeOperationResult Facade::DrawScene() {
  FacadeOperationResult operation_result;
  if (scene_.GetFigures().empty()) {
    operation_result.SetErrorMessage("Отсутствует загруженная сцена");
  } else {
    scene_drawer_.DrawScene(scene_);
  }

  return operation_result;
}

void Facade::MoveScene(double x_offset, double y_offset, double z_offset) {
  transform_handler_.HandleOffsets(x_offset, y_offset, z_offset);
  TransformMatrix matrix =
      TransformMatrixBuilder::CreateMoveMatrix(x_offset, y_offset, z_offset);
  scene_.TransformFigures(matrix);
  scene_drawer_.SetCoordinates(scene_);
}

void Facade::RotateScene(double x_angle, double y_angle, double z_angle) {
  transform_handler_.HandleRotationAngles(x_angle, y_angle, z_angle);

  TransformMatrix matrix = TransformMatrixBuilder::CreateMoveMatrix(
      -transform_handler_.GetCurrentTransfomations().x_offset,
      -transform_handler_.GetCurrentTransfomations().y_offset,
      -transform_handler_.GetCurrentTransfomations().z_offset);
  scene_.TransformFigures(matrix);

  matrix =
      TransformMatrixBuilder::CreateRotationMatrix(x_angle, y_angle, z_angle);
  scene_.TransformFigures(matrix);

  matrix = TransformMatrixBuilder::CreateMoveMatrix(
      transform_handler_.GetCurrentTransfomations().x_offset,
      transform_handler_.GetCurrentTransfomations().y_offset,
      transform_handler_.GetCurrentTransfomations().z_offset);
  scene_.TransformFigures(matrix);

  scene_drawer_.SetCoordinates(scene_);
}

void Facade::ScaleScene(double new_factor) {
  transform_handler_.HandleScale(new_factor);
  TransformMatrix matrix =
      TransformMatrixBuilder::CreateScaleMatrix(new_factor);
  scene_.TransformFigures(matrix);
  scene_drawer_.SetCoordinates(scene_);
}

const vector<unsigned int>* Facade::GetIndicesRef() const {
  return scene_drawer_.GetIndexesRef();
};
const vector<double>* Facade::GetCoordinatesRef() const {
  return scene_drawer_.GetCoordinatesRef();
}

const Settings& Facade::GetStateRef() const {
  return settings_store_.GetStateRef();
}

}  // namespace s21
