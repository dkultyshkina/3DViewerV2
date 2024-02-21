/*!
\file
\brief Исходный файл OffsetScene.h с определением класса класса для смещения
модели

Данный файл содержит в себе определение класса OffsetScene и его методов
смещения модели относительно камеры
*/
#ifndef SRC_MODEL_OFFSETSCENE_H_
#define SRC_MODEL_OFFSETSCENE_H_

#include <iostream>
#include <vector>

#include "Model.h"

namespace viewer {

class OffsetScene {
 public:
  OffsetScene();
  OffsetScene(std::vector<double> new_verticies);
  ~OffsetScene();

  std::vector<double> GetOffset();

 private:
  std::vector<double> verticies_;
  std::vector<double> offset_;

  void СalculatingOffset();
};
};      // namespace viewer
#endif  // SRC_MODEL_OFFSETSCENE_H_