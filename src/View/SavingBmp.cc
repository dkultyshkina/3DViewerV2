/*!
\file
\brief Исходный файл SavingBmp.h

Данный файл содержит в себе определение класса SavingBmp
*/
#include "SavingBmp.h"

namespace viewer {

/*!
Базовый конструктор
*/
SavingBmp::SavingBmp() = default;

/*!
Параметризованный конструктор
\param[out] new_scene переменная, которая хранит в себе указател на экземпляр
класса QOpenGLWidget
*/
SavingBmp::SavingBmp(QOpenGLWidget* new_scene) : scene_(new_scene){};

/*!
Деструтор
*/
SavingBmp::~SavingBmp() = default;

/*!
Метод, который сохраняет модель в файл с типом .bmp
*/
void SavingBmp::SaveModel() {
  QString base_filename = "img.bmp";
  QString save_in_file = QFileDialog::getSaveFileName(
      scene_, "Save your file:", QDir::currentPath() + "/" + base_filename,
      "BMP File (*.bmp)");
  QFile file(save_in_file);
  if (!file.open(QIODevice::WriteOnly) || save_in_file.isEmpty()) {
    throw std::string("Couldn't take a screenshot!");
  } else {
    QRect size_scene(0, 0, scene_->width(), scene_->height());
    QPixmap pix_scene = scene_->grab(size_scene);
    bool result = pix_scene.copy(size_scene).toImage().save(save_in_file);
    if (result == false) {
      throw std::string("Couldn't take a screenshot!");
    }
  }
}

}  // namespace viewer
