/*!
\file
\brief Заголовочный файл Facade.h с определением соответствующего класса шаблона
проектирования фасад в проекте 3DViewer

Данный файл содержит в себе определение класса Facade и его методов для
реализации шаблона проектирования фасад, с помощью которого мы сводим все
внешние вызовы к одному объекту модели, делегирующему их соответствующим
объектам модели
*/
#ifndef SRC_MODEL_FACADE_H_
#define SRC_MODEL_FACADE_H_

#include <iostream>
#include <vector>

#include "BaseFileReader.h"
#include "FacadeOperationResult.h"
#include "FileReader.h"
#include "MovedModel.h"
#include "OffsetScene.h"
#include "RotatedModel.h"
#include "ScaledModel.h"
#include "TransformModelBuilder.h"

namespace viewer {

class Facade {
 public:
  Facade();
  ~Facade();

  Model* GetModel();
  std::vector<double> GetOffset();

  FacadeOperationResult LoadScene(std::string path_file);
  FacadeOperationResult MoveModel(double x, double y, double z);
  FacadeOperationResult RotateModel(double x, double y, double z);
  FacadeOperationResult ScaleModel(double x, double y, double z);

 private:
  BaseFileReader* file_reader_;  //< указатель на экземпляр класса чтения файла
  Model* model_;  //< экземляр класса модели для отрисовки
  TransformModelBuilder*
      build_;  //< указатель на экземпляр класса изменения модели
  // ConservationModelStrategy* file_saver_;
  OffsetScene* offset_;

  void CheckThrowInTransformation();
  void NormalizationModel();
  void ClearBuild();
};
};      // namespace viewer
#endif  // SRC_MODEL_FACADE_H_