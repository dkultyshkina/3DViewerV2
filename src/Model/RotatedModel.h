/*!
\file
\brief Исходный файл RotatedModel.h с определением класса для вращения модели

Данный файл содержит в себе определение класса RotatedModel и его методов для
вращения модели
*/
#ifndef SRC_MODEL_ROTATEDMODEL_H_
#define SRC_MODEL_ROTATEDMODEL_H_

#include <math.h>

#include <iostream>

#include "Model.h"
#include "TransformModelBuilder.h"

namespace viewer {

class RotatedModel : public TransformModelBuilder {
 public:
  RotatedModel(Model& new_model);
  ~RotatedModel();

  Model* ChangeModelX(double x) override;
  Model* ChangeModelY(double y) override;
  Model* ChangeModelZ(double z) override;

 private:
  Model& model_;
};
};      // namespace viewer
#endif  // SRC_MODEL_ROTATEDMODEL_H_