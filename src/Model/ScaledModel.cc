/*!
\file
\brief Исходный файл ScaledModel.h с описанием класса для маштабирования модели

Данный файл содержит в себе описание класса ScaledModel и его методов для
маштабирования модели
*/
#include "ScaledModel.h"

namespace viewer {

/*
Параметризированный конструктор
\param[in] new_model Переменная, которая содержит значение модели
*/
ScaledModel::ScaledModel(Model& new_model) : model_(new_model){};

/*
Деструктор
*/
ScaledModel::~ScaledModel() = default;

/*!
Метод класса,  в которой выполняется маштабирование модели на требуемое значение
по оси x \param[in] x Переменная, которая содержит значение на которое вращается
модель \return экземпляр класса модели
*/
Model* ScaledModel::ChangeModelX(double x) {
  std::vector<double> vector_vertices_ = model_.GetVertices();
  for (size_t i = 0; i < vector_vertices_.size(); i += 3) {
    vector_vertices_[i] *= x;
  }
  model_.SetVertices(vector_vertices_);
  return &(model_);
}

/*!
Метод класса,  в которой выполняется маштабирование модели на требуемое значение
по оси y \param[in] y Переменная, которая содержит значение на которое вращается
матрица \return экземпляр класса модели
*/
Model* ScaledModel::ChangeModelY(double y) {
  std::vector<double> vector_vertices_ = model_.GetVertices();
  for (size_t i = 1; i < vector_vertices_.size(); i += 3) {
    vector_vertices_[i] *= y;
  }
  model_.SetVertices(vector_vertices_);
  return &(model_);
}

/*!
Метод класса, в которой выполняется маштабирование модели на требуемое значение
по оси z \param[in] z Переменная, которая содержит значение на которое вращается
матрица \return экземпляр класса модели
*/
Model* ScaledModel::ChangeModelZ(double z) {
  std::vector<double> vector_vertices_ = model_.GetVertices();
  for (size_t i = 2; i < vector_vertices_.size(); i += 3) {
    vector_vertices_[i] *= z;
  }
  model_.SetVertices(vector_vertices_);
  return &(model_);
}

}  // namespace viewer