/*!
\file
\brief Исходный файл Facade.h с реализацией шаблона проектирования фасад в
проекте 3DViewer

Данный файл содержит в себе описание класса Facade и его методов для реализации
шаблона проектирования фасад, с помощью которого мы сводим все внешние вызовы к
одному объекту модели, делегирующему их соответствующим объектам модели
*/

#include "Facade.h"

namespace viewer {

/*
Базовый конструктор
*/
Facade::Facade()
    : file_reader_(nullptr),
      model_(nullptr),
      build_(nullptr),
      offset_(nullptr) {}

/*
Деструктор
*/
Facade::~Facade() {
  if (file_reader_ != nullptr) {
    delete file_reader_;
  }
  if (offset_ != nullptr) {
    delete offset_;
  }
};

/*
Получение значение поля класса model_
\return Значение model_
*/
Model* Facade::GetModel() { return model_; }

std::vector<double> Facade::GetOffset() {
  if (offset_ != nullptr) {
    return offset_->GetOffset();
  }
  std::vector<double> v = {0, 0, 0, 0, 0, 0};
  return v;
}

/*!
Метод класса, в котором выполняется загрузка модели из файла \param[in]
path_file переменная, в которой хранится путь до файла с моделью \return
Возвращает экземляр класса с результатом операции
*/
FacadeOperationResult Facade::LoadScene(std::string path_file) {
  FacadeOperationResult result_operation = FacadeOperationResult();
  try {
    file_reader_ = new FileReader(path_file);
    model_ = file_reader_->ReadModel(path_file);
    std::vector<double> v = (*model_).GetVertices();
    offset_ = new OffsetScene(v);
    NormalizationModel();
  } catch (std::string error) {
    result_operation.SetErrorMessage(error);
    result_operation.SetResultOfOperation(false);
  }
  return result_operation;
}

/*!
Метод класса, в котором выполняется перемещение модели
 \param[in] x Переменная, которая содержит значение x на которое
сдвигается модель
 \param[in] y Переменная, которая содержит значение y на которое
сдвигается модель
 \param[in] z Переменная, которая содержит значение z на которое
сдвигается модель
\return Возвращает экземляр класса с результатом операции
*/
FacadeOperationResult Facade::MoveModel(double x, double y, double z) {
  FacadeOperationResult result_operation = FacadeOperationResult();
  try {
    CheckThrowInTransformation();
    build_ = new MovedModel(*model_);
    if (abs(x) > 1e-7) {
      build_->ChangeModelX(x);
    }
    if (abs(y) > 1e-7) {
      build_->ChangeModelY(y);
    }
    if (abs(z) > 1e-7) {
      build_->ChangeModelZ(z);
    }
    ClearBuild();
  } catch (std::string error) {
    result_operation.SetErrorMessage(error);
    result_operation.SetResultOfOperation(false);
  }
  return result_operation;
}

/*!
Метод класса, в котором выполняется вращение модели
 \param[in] x Переменная, которая содержит значение x на которое
вращается модель
 \param[in] y Переменная, которая содержит значение y на которое
вращается модель
 \param[in] z Переменная, которая содержит значение z на которое
вращается модель
\return Возвращает экземляр класса с результатом операции
*/
FacadeOperationResult Facade::RotateModel(double x, double y, double z) {
  FacadeOperationResult result_operation = FacadeOperationResult();
  try {
    CheckThrowInTransformation();
    build_ = new RotatedModel(*model_);
    if (abs(x) > 1e-7) {
      model_ = build_->ChangeModelX(x);
    }
    if (abs(y) > 1e-7) {
      model_ = build_->ChangeModelY(y);
    }
    if (abs(z) > 1e-7) {
      model_ = build_->ChangeModelZ(z);
    }
    ClearBuild();
  } catch (std::string error) {
    result_operation.SetErrorMessage(error);
    result_operation.SetResultOfOperation(false);
  }
  return result_operation;
}

/*!
Метод класса, в котором выполняется маштабирование модели
 \param[in] x Переменная, которая содержит значение x на которое
маштабируется модель
 \param[in] y Переменная, которая содержит значение y на которое
маштабируется модель
 \param[in] z Переменная, которая содержит значение z на которое
маштабируется модель
\return Возвращает экземляр класса с результатом операции
*/
FacadeOperationResult Facade::ScaleModel(double x, double y, double z) {
  FacadeOperationResult result_operation = FacadeOperationResult();
  try {
    CheckThrowInTransformation();
    build_ = new ScaledModel(*model_);
    if (abs(x) > 1e-7) {
      if (x > 0) {
        model_ = build_->ChangeModelX(x);
      } else {
        model_ = build_->ChangeModelX(1.0 / abs(x));
      }
    }
    if (abs(y) > 1e-7) {
      if (y > 0) {
        model_ = build_->ChangeModelY(y);
      } else {
        model_ = build_->ChangeModelY(1.0 / abs(y));
      }
    }
    if (abs(z) > 1e-7) {
      if (z > 0) {
        model_ = build_->ChangeModelZ(z);
      } else {
        model_ = build_->ChangeModelZ(1.0 / abs(z));
      }
    }
    ClearBuild();
  } catch (std::string error) {
    result_operation.SetErrorMessage(error);
    result_operation.SetResultOfOperation(false);
  }
  return result_operation;
}

/*!
Метод класса, проверяющий существование модели
*/
void Facade::CheckThrowInTransformation() {
  if (model_ == nullptr) {
    throw std::string("Error! Empty model");
  }
}

/*!
Метод нормализации модели
*/
void Facade::NormalizationModel() {
  std::vector<double> vertices = (*model_).GetVertices();
  if (vertices.size() < 3) {
    return;
  }
  double max_delta_offset = 0;
  std::vector<double> offset = GetOffset();
  for (size_t i = 0; i < 3; ++i) {
    if (max_delta_offset < offset[3 + i] - offset[i]) {
      max_delta_offset = offset[3 + i] - offset[i];
    }
  }
  MoveModel(-(offset[3] + offset[0]) / 2, -(offset[4] + offset[1]) / 2,
            -(offset[2] + offset[5]) / 2);
  ScaleModel(3 / max_delta_offset, 3 / max_delta_offset, 3 / max_delta_offset);
}

/*!
Метод, который очищает указатель на поле данных build_
*/
void Facade::ClearBuild() {
  if (build_ != nullptr) {
    delete build_;
  }
};
}  // namespace viewer