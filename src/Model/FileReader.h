/*!
\file
\brief Исходный файл FileReader.h с определением класса для чтения модели из
файла

Данный файл содержит в себе определение класса FileReader и его методов для
чтения модели из файла
*/
#ifndef SRC_MODEL_FILEREADER_H_
#define SRC_MODEL_FILEREADER_H_

#include <fstream>
#include <sstream>
#include <string>

#include "BaseFileReader.h"
#include "Model.h"

namespace viewer {

class FileReader : public BaseFileReader {
 public:
  FileReader();
  FileReader(std::string path_file);
  ~FileReader();

  Model* ReadModel(std::string file_path) override;

 private:
  Model model_;  //< экземпляр класса модели
  std::string
      file_name_;  //< переменная, в которой хранится путь к файлу с моделью
  std::ifstream stream_file_;  //< файловый поток

  void CheckThrowOpenFile();
  void SaveAllElements();
  void SavePolygonData(std::string line);
};

};      // namespace viewer
#endif  // SRC_MODEL_FILEREADER_H_