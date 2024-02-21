/*!
\file
\brief Исходный файл BaseFileReader.h

Данный файл содержит в себе описание класса BaseFileReader и его виртуального
метода
*/

#ifndef SRC_MODEL_BASEFILEREADER_H_
#define SRC_MODEL_BASEFILEREADER_H_

#include <iostream>

#include "Model.h"

namespace viewer {

class BaseFileReader {
 public:
  virtual ~BaseFileReader() = default;
  virtual Model* ReadModel(std::string file_path) = 0;
};
};      // namespace viewer
#endif  // SRC_MODEL_BASEFILEREADER_H_