/*!
\file
\brief Исходный файл MovedModel.h с определением класса для перемещения модели

Данный файл содержит в себе определение класса RotatedModel и его методов для
для перемещения модели
*/
#ifndef SRC_MODEL_MOVEDMODEL_H_
#define SRC_MODEL_MOVEDMODEL_H_

#include <iostream>

#include "Model.h"
#include "TransformModelBuilder.h"

namespace viewer {

class MovedModel : public TransformModelBuilder {
 public:
  MovedModel(Model& model);
  ~MovedModel();

  Model* ChangeModelX(double x) override;
  Model* ChangeModelY(double y) override;
  Model* ChangeModelZ(double z) override;

 private:
  Model& model_;
};
};      // namespace viewer
#endif  // SRC_MODEL_MOVEDMODEL_H_