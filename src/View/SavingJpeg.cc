/*!
\file
\brief Исходный файл SavingJpeg.h

Данный файл содержит в себе определение класса SavingJpeg
*/
#include "SavingJpeg.h"

namespace viewer {

/*!
Базовый конструктор
*/
SavingJpeg::SavingJpeg() : scene_(nullptr){};

/*!
Параметризованный конструктор
\param[out] new_scene переменная, которая хранит в себе указател на экземпляр
класса QOpenGLWidget
*/
SavingJpeg::SavingJpeg(QOpenGLWidget* new_scene_) : scene_(new_scene_){};

/*!
Деструтор
*/
SavingJpeg::~SavingJpeg() = default;

/*!
Метод, который сохраняет модель в файл с типом .jpeg
*/
void SavingJpeg::SaveModel() {
  QString base_filename = "img.jpeg";
  QString save_in_file = QFileDialog::getSaveFileName(
      scene_, "Save your file:", QDir::currentPath() + "/" + base_filename,
      "JPEG File (*.jpeg)");
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
