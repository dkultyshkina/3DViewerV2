/*!
\file
\brief Исходный файл TransformModelBuilder.h

Данный файл содержит в себе описание класса TransformModelBuilder и его
виртуальных методов
*/
#ifndef SRC_MODEL_TRANSFORMMODELBUILDER_H_
#define SRC_MODEL_TRANSFORMMODELBUILDER_H_

#include <iostream>

#include "Model.h"

namespace viewer {

class TransformModelBuilder {
 public:
  virtual ~TransformModelBuilder() = default;
  virtual Model* ChangeModelY(double x) = 0;
  virtual Model* ChangeModelX(double y) = 0;
  virtual Model* ChangeModelZ(double z) = 0;
};
};      // namespace viewer
#endif  // SRC_MODEL_TRANSFORMMODELBUILDER_H_