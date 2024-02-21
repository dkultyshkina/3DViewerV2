/*!
\file
\brief Исходный файл RotatedModel.сс с описанием класса для вращения модели

Данный файл содержит в себе описание класса RotatedModel и его методов для
вращения модели
*/
#include "RotatedModel.h"

namespace viewer {
/*
Параметризированный конструктор
\param[in] new_model Переменная, которая содержит значение модели
*/
RotatedModel::RotatedModel(Model& new_model) : model_(new_model){};

/*
Деструктор
*/
RotatedModel::~RotatedModel() = default;

/*!
Метод класса, в которой выполняется вращение модели по оси Х на требуемое
значение \param[in] x Переменная, которая содержит значение на которое
вращается модель \return экземпляр класса модели
*/
Model* RotatedModel::ChangeModelX(double x) {
  std::vector<double>& vector_vertices_ = model_.GetVertices();
  for (size_t i = 0; i < vector_vertices_.size(); i += 3) {
    double temp_y = vector_vertices_[i + 1];
    double temp_z = vector_vertices_[i + 2];
    vector_vertices_[i + 1] = temp_y * cos(x) + sin(x) * temp_z;
    vector_vertices_[i + 2] = (-1 * temp_y) * sin(x) + cos(x) * temp_z;
  }
  return &(model_);
}

/*!
Метод класса, в которой выполняется вращение модели по оси Y на требуемое
значение \param[in] y Переменная, которая содержит значение на которое
вращается матрица \return экземпляр класса модели
*/
Model* RotatedModel::ChangeModelY(double y) {
  std::vector<double>& vector_vertices_ = model_.GetVertices();
  for (size_t i = 0; i < vector_vertices_.size(); i += 3) {
    double temp_x = vector_vertices_[i];
    double temp_z = vector_vertices_[i + 2];
    vector_vertices_[i] = temp_x * cos(y) + sin(y) * temp_z;
    vector_vertices_[i + 2] = (-1 * temp_x) * sin(y) + cos(y) * temp_z;
  }
  return &(model_);
}

/*!
Метод класса, в которой выполняется вращение матрицы по оси Z на требуемое
значение \param[in] z Переменная, которая содержит значение на которое
вращается матрица \return экземпляр класса модели
*/
Model* RotatedModel::ChangeModelZ(double z) {
  std::vector<double>& vector_vertices_ = model_.GetVertices();
  for (size_t i = 0; i < vector_vertices_.size(); i += 3) {
    double temp_x = vector_vertices_[i];
    double temp_y = vector_vertices_[i + 1];
    vector_vertices_[i] = temp_x * cos(z) + sin(z) * temp_y;
    vector_vertices_[i + 1] = (-1 * temp_x) * sin(z) + cos(z) * temp_y;
  }
  return &(model_);
}

}  // namespace viewer