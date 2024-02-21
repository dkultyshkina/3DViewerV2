/*!
\file
\brief Исходный файл FacadeOperationResult.сс с определением класса для
демонстрации итогового результата выполнения операции

Данный файл содержит в себе определение класса FacadeOperationResult и его
методов для демонстрации итогового результата выполнения операции: текст ошибки
и успех/неуспех
*/

#ifndef SRC_MODEL_FACADEOPERATIONRESULT_H_
#define SRC_MODEL_FACADEOPERATIONRESULT_H_

#include <iostream>
#include <string>

namespace viewer {

class FacadeOperationResult {
 public:
  FacadeOperationResult();
  ~FacadeOperationResult();

  std::string GetErrorMessage();
  bool GetResultOfOperation();
  void SetErrorMessage(std::string new_error_message);
  void SetResultOfOperation(bool new_result);

 private:
  std::string error_message_;  //< переменная, в которой храниться текст ошибки
  bool result_;  //< переменная, которая содержит в себе значение успешности или
                 // провала выполнения
};
};      // namespace viewer
#endif  // SRC_MODEL_FACADEOPERATIONRESULT_H_