/*!
\file
\brief Исходный файл TypeSavingModel.h

Данный файл содержит в себе определение класса TypeSavingModel
*/

#ifndef SRC_VIEW_TYPESAVINGMODELH_
#define SRC_VIEW_TYPESAVINGMODELH_

#include <iostream>

#include "SavingModelStrategy.h"

namespace viewer {

class TypeSavingModel {
 public:
  TypeSavingModel();
  TypeSavingModel(SavingModelStrategy* new_type);
  ~TypeSavingModel();

  void SaveModel();

 private:
  SavingModelStrategy*
      type_;  //< указатель на экземпляр класса стратегии сохранения модели
};

};      // namespace viewer
#endif  // SRC_VIEW_TYPESAVINGMODELH_
