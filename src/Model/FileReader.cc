/*!
\file
\brief Исходный файл FileReader.сс с описанием класса для чтения модели из файла

Данный файл содержит в себе описанием класса FileReader и его методов для чтения
модели из файла
*/
#include "FileReader.h"

namespace viewer {
/*
Базовый конструктор
*/
FileReader::FileReader() = default;

/*
Параметризированный конструктор
\param[in] path_file Переменная, которая содержит значение пути до файла с
моделью
*/
FileReader::FileReader(std::string path_file)
    : file_name_(path_file), stream_file_(path_file){};

/*
Деструктор
*/
FileReader::~FileReader() = default;

/*!
Публичный метод класса, в котором выполняется чтение модели из файла \param[in]
file_path переменная, в которой хранится путь до файла с моделью \return
Возвращает экземляр класса модели
*/
Model* FileReader::ReadModel(std::string file_path) {
  file_name_ = file_path;
  if (!stream_file_.is_open() || stream_file_.peek() == EOF) {
    throw std::string{"File doesn't open!"};
  }
  SaveAllElements();
  return &model_;
}

/*!
Cохранение всех элементов в модель
*/
void FileReader::SaveAllElements() {
  model_ = Model();
  stream_file_.seekg(0);
  std::string line;
  size_t p = 1, i = 1;
  double first = 0.0, second = 0.0, third = 0.0;
  while (getline(stream_file_, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      sscanf(line.c_str(), "%*s %lf %lf %lf", &first, &second, &third);
      model_.AddVertices(first);
      model_.AddVertices(second);
      model_.AddVertices(third);
      i++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      // Передача строки с отделением первых двух символов ("f ")
      SavePolygonData(line.substr(2));
      p++;
    }
  }
  stream_file_.close();
}

/*!
Cохранение всех элементов в линию
*/
void FileReader::SavePolygonData(std::string input) {
  // Разбиваем строку на токены, используя пробельные символы в качестве
  // разделителей
  std::istringstream iss(input);
  std::string token;
  int first_num = 0, current_num = 0;

  // Обработка первого числа линии
  iss >> token;
  auto slash_pos = token.find('/');
  if (slash_pos != std::string::npos) {
    first_num = std::stoi(token.substr(0, slash_pos)) - 1;
  } else {
    first_num = std::stoi(token) - 1;
  }
  model_.AddLines(first_num);

  while (iss >> token) {
    // Ищем символ "/"
    slash_pos = token.find('/');
    if (slash_pos != std::string::npos) {
      // Если символ "/" найден, берем только то, что до него
      current_num = std::stoi(token.substr(0, slash_pos)) - 1;
    } else {
      // Если символ "/" не найден, берем весь токен
      current_num = std::stoi(token) - 1;
    }

    model_.AddLines(current_num);
    model_.AddLines(current_num);
  }
  // Для замыкания фигуры
  model_.AddLines(first_num);
}
}  // namespace viewer
