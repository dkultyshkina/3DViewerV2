/*!
\file
\brief Исходный файл ScaledModel.h с определением класса для маштабирования
модели

Данный файл содержит в себе определение класса ScaledModel и его методов для
маштабирования модели
*/
#ifndef SRC_MODEL_SCALEDMODEL_H_
#define SRC_MODEL_SCALEDMODEL_H_

#include <iostream>

#include "Model.h"
#include "TransformModelBuilder.h"

namespace viewer {

class ScaledModel : public TransformModelBuilder {
 public:
  ScaledModel() = delete;
  ScaledModel(Model& model);
  ~ScaledModel();

  Model* ChangeModelX(double x) override;
  Model* ChangeModelY(double y) override;
  Model* ChangeModelZ(double z) override;

 private:
  Model& model_;  //< экземпляр класса модели
};
};      // namespace viewer
#endif  // SRC_MODEL_SCALEDMODEL_H_