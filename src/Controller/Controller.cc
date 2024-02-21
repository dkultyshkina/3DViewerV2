#include "Controller.h"

namespace viewer {

Controller::Controller(viewer::View& view, viewer::Facade& model)
    : view_(view), model_(model) {
  // Соединение контроллера с моделью по средствам слотов и сигналов
  QObject::connect(&view_, &View::handleOpenFile, this,
                   &Controller::ProcLoadFile);
  QObject::connect(&view_, &View::handleMove, this, &Controller::ProcMoveModel);
  QObject::connect(&view_, &View::handleRotate, this,
                   &Controller::ProcRotateModel);
  QObject::connect(&view_, &View::handleScale, this,
                   &Controller::ProcScaleModel);
}

void Controller::ProcLoadFile(QString filepath) {
  model_.LoadScene(filepath.toStdString());

  Model* data_ = model_.GetModel();
  view_.setShowData(data_->GetVertices(), data_->GetLines());

  int count_vertex = data_->GetVertices().size() / 3;
  int count_edge = data_->GetLines().size() / 2;
  view_.showFileDetails(filepath, count_vertex, count_edge);
}

void Controller::ProcMoveModel(double x, double y, double z) {
  viewer::FacadeOperationResult a = model_.MoveModel(x, y, z);
  std::cerr << a.GetErrorMessage();
  view_.reDraw();
}

void Controller::ProcRotateModel(double x, double y, double z) {
  viewer::FacadeOperationResult a =
      model_.RotateModel(x * M_PI / 180, y * M_PI / 180, z * M_PI / 180);
  std::cerr << a.GetErrorMessage();
  view_.reDraw();
}

void Controller::ProcScaleModel(double coef) {
  viewer::FacadeOperationResult a = model_.ScaleModel(coef, coef, coef);
  std::cerr << a.GetErrorMessage();
  view_.reDraw();
}

}  // namespace viewer
