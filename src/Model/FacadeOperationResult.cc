/*!
\file
\brief Исходный файл FacadeOperationResult.сс с реализацией класса для
демонстрации итогового результата выполнения операции

Данный файл содержит в себе описание класса FacadeOperationResult и его методов
для демонстрации итогового результата выполнения операции: текст ошибки и
успех/неуспех
*/

#include "FacadeOperationResult.h"

namespace viewer {

/*
Базовый конструктор
*/
FacadeOperationResult::FacadeOperationResult()
    : error_message_(), result_(true) {}

/*
Деструктор
*/
FacadeOperationResult::~FacadeOperationResult() = default;

/*
Получение значение поля класса error_message_
\return Значение error_message_
*/
std::string FacadeOperationResult::GetErrorMessage() { return error_message_; }

/*
Получение значение поля класса result_
\return Значение result_
*/
bool FacadeOperationResult::GetResultOfOperation() { return result_; }

/*
Изменение значения поля класса error_message_
\return Значение error_message_
*/
void FacadeOperationResult::SetErrorMessage(std::string new_error_message) {
  error_message_ = new_error_message;
};

/*
Изменение значения поля класса new_result_
\return Значение new_result_
*/
void FacadeOperationResult::SetResultOfOperation(bool new_result) {
  result_ = new_result;
};

}  // namespace viewer