/*!
\file
\brief Исходный файл SavingBmp.h

Данный файл содержит в себе описание класса SavingBmp
*/

#ifndef SRC_VIEW_SAVINGBMP_H_
#define SRC_VIEW_SAVINGBMP_H_

#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QRect>
#include <iostream>

#include "../QtGifImage-master/src/gifimage/qgifimage.h"
#include "SavingModelStrategy.h"

namespace viewer {

class SavingBmp : public SavingModelStrategy {
 public:
  friend class MyGLWidget;

  SavingBmp();
  SavingBmp(QOpenGLWidget* new_scene_);
  ~SavingBmp();

  void SaveModel() override;

 private:
  QOpenGLWidget* scene_;
};

};      // namespace viewer
#endif  // SRC_VIEW_SAVINGBMP_H_
