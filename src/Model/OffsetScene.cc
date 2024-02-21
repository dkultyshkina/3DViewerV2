/*!
\file
\brief Исходный файл OffsetScene.h с описанием класса для смещения модели

Данный файл содержит в себе определение класса OffsetScene и определения
смещения модели относительно камеры
*/
#include "OffsetScene.h"

namespace viewer {
/*!
Базовый конструктор
*/
OffsetScene::OffsetScene() = default;

/*!
Параметризованный конструктор
\param[in] new_verticies
*/
OffsetScene::OffsetScene(std::vector<double> new_verticies)
    : verticies_(new_verticies) {
  if (verticies_.size() > 3) {
    СalculatingOffset();
  }
};

/*!
Деструктор
*/
OffsetScene::~OffsetScene() = default;

/*!
Метод, возвращающий вектор с максимальными и минимальными значениями точек
\return вектор с максимальными и минимальными значениями точек
*/
std::vector<double> OffsetScene::GetOffset() { return offset_; };

/*!
Метод, который считаем максимальные и минимальные точки по оси x, y, z
*/
void OffsetScene::СalculatingOffset() {
  double offset_x_min = verticies_[0];
  double offset_y_min = verticies_[1];
  double offset_z_min = verticies_[2];
  double offset_x_max = 0;
  double offset_y_max = 0;
  double offset_z_max = 0;
  for (size_t i = 0; i < verticies_.size(); i += 3) {
    if (verticies_[i] < offset_x_min) {
      offset_x_min = verticies_[i];
    }
    if (verticies_[i] > offset_x_max) {
      offset_x_max = verticies_[i];
    }
  }
  for (size_t i = 1; i < verticies_.size(); i += 3) {
    if (verticies_[i] < offset_y_min) {
      offset_y_min = verticies_[i];
    }
    if (verticies_[i] > offset_y_max) {
      offset_y_max = verticies_[i];
    }
  }
  for (size_t i = 2; i < verticies_.size(); i += 3) {
    if (verticies_[i] < offset_z_min) {
      offset_z_min = verticies_[i];
    }
    if (verticies_[i] > offset_z_max) {
      offset_z_max = verticies_[i];
    }
  }
  offset_.push_back(offset_x_min);
  offset_.push_back(offset_y_min);
  offset_.push_back(offset_z_min);
  offset_.push_back(offset_x_max);
  offset_.push_back(offset_y_max);
  offset_.push_back(offset_z_max);
};

}  // namespace viewer
