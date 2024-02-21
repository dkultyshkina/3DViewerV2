/*!
\file
\brief Исходный файл Model.сс с описанием класса для вращения модели

Данный файл содержит в себе описанием класса Model и его методов для вращения
модели
*/
#include "Model.h"

namespace viewer {
/*
Базовый конструктор
*/
Model::Model() = default;

/*
Параметризированный конструктор
\param[in] new_verticies Переменная, которая содержит значение вектора с
вершинами \param[in] new_lines Переменная, которая содержит значение вектора с
линиями
*/
Model::Model(std::vector<double> new_verticies,
             std::vector<unsigned int> new_lines)
    : vector_vertices_(new_verticies), vector_lines_(new_lines){};

/*
Деструктор
*/
Model::~Model() = default;

/*
Получение значение поля класса vector_vertices_
\return Значение vector_vertices_
*/
std::vector<double> &Model::GetVertices() { return vector_vertices_; }

/*
Получение значение поля класса vector_lines_
\return Значение vector_lines_
*/
std::vector<unsigned int> &Model::GetLines() { return vector_lines_; }

/*
Изменение значение поля класса vector_vertices_
\param[in] new_vertices Новое значение vector_vertices_
*/
void Model::SetVertices(std::vector<double> new_vertices) {
  vector_vertices_ = new_vertices;
};

/*
Изменение значение поля класса vector_lines_
\param[in] new_lines Новое значение vector_lines_
*/
void Model::SetLines(std::vector<unsigned int> new_lines) {
  vector_lines_ = new_lines;
};

/*
Добавление элемента в вектор вершин
\param[in] element Новое значение для добавления vector_vertices_
*/
void Model::AddVertices(double element) {
  vector_vertices_.push_back(element);
};

/*
Добавление элемента в вектор вершин
\param[in] element Новое значение для добавления в vector_lines_
*/
void Model::AddLines(unsigned int element) {
  vector_lines_.push_back(element);
};

}  // namespace viewer
