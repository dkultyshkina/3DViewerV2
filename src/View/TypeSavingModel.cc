/*!
\file
\brief Исходный файл TypeSavingModel.h

Данный файл содержит в себе описание класса TypeSavingModel
*/
#include "TypeSavingModel.h"

namespace viewer {
/*!
Базовый конструктор
*/
TypeSavingModel::TypeSavingModel() : type_(nullptr){};

/*!
Параметризованный конструктор
\param[out] new_type Параметр типа сохранения модели
*/
TypeSavingModel::TypeSavingModel(SavingModelStrategy* new_type) {
  type_ = new_type;
}

/*!
Деструктор
*/
TypeSavingModel::~TypeSavingModel() = default;

/*!
Метод для выполнения сохранения модели
*/
void TypeSavingModel::SaveModel() {
  try {
    if (type_ != nullptr) {
      type_->SaveModel();
    }
  } catch (std::string error) {
    throw std::string("Error!");
  }
}
}  // namespace viewer
