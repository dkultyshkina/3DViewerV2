/*!
\file
\brief Исходный файл MovedModel.h с описанием класса для перемещения модели

Данный файл содержит в себе определение класса MovedModel и его методов для
перемещения модели
*/
#include "MovedModel.h"

namespace viewer {

/*
Параметризированный конструктор
\param[in] new_model Переменная, которая содержит значение модели
*/
MovedModel::MovedModel(Model& new_model) : model_(new_model){};

/*
Деструктор
*/
MovedModel::~MovedModel() = default;

/*!
Метод класса,  в которой выполняется перемещение модели на требуемое значение по
оси x \param[in] x Переменная, которая содержит значение на которое вращается
модель \return экземпляр класса модели
*/
Model* MovedModel::ChangeModelX(double x) {
  std::vector<double>& vector_vertices_ = model_.GetVertices();
  for (size_t i = 0; i < vector_vertices_.size(); i += 3) {
    vector_vertices_[i] += x;
  }
  return &(model_);
};

/*!
Метод класса,  в которой выполняется перемещение модели на требуемое значение по
оси y \param[in] y Переменная, которая содержит значение на которое вращается
матрица \return экземпляр класса модели
*/
Model* MovedModel::ChangeModelY(double y) {
  std::vector<double>& vector_vertices_ = model_.GetVertices();
  for (size_t i = 1; i < vector_vertices_.size(); i += 3) {
    vector_vertices_[i] += y;
  }
  return &(model_);
};

/*!
Метод класса, в которой выполняется перемещение модели на требуемое значение по
оси z \param[in] z Переменная, которая содержит значение на которое вращается
матрица \return экземпляр класса модели
*/
Model* MovedModel::ChangeModelZ(double z) {
  std::vector<double>& vector_vertices_ = model_.GetVertices();
  for (size_t i = 2; i < vector_vertices_.size(); i += 3) {
    vector_vertices_[i] += z;
  }
  return &(model_);
};

}  // namespace viewer