/*!
\file
\brief Исходный файл Model.h с определением класса для определения модели

Данный файл содержит в себе определение класса Model и его методов для
определение модели
*/
#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <iostream>
#include <vector>

#include "FacadeOperationResult.h"

namespace viewer {

class Model {
 public:
  Model();
  Model(std::vector<double> new_vertices, std::vector<unsigned int> new_lines);
  ~Model();

  std::vector<double>& GetVertices();
  std::vector<unsigned int>& GetLines();
  void SetVertices(std::vector<double> new_vertices);
  void SetLines(std::vector<unsigned int> new_lines);
  void AddVertices(double element);
  void AddLines(unsigned int element);

 private:
  std::vector<double> vector_vertices_;     //< вектор вершин
  std::vector<unsigned int> vector_lines_;  //< вектор линий
};

};      // namespace viewer
#endif  // CPP4_3DVIEWER_SRC_MODEL_MODEL_H_