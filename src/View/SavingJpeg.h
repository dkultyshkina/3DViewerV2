/*!
\file
\brief Исходный файл SavingJpeg.h

Данный файл содержит в себе описание класса SavingJpeg
*/

#ifndef SRC_VIEW_SAVINGJPEG_H_
#define SRC_VIEW_SAVINGJPEG_H_

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QRect>
#include <iostream>

#include "../QtGifImage-master/src/gifimage/qgifimage.h"
#include "SavingModelStrategy.h"

namespace viewer {

class SavingJpeg : public SavingModelStrategy {
 public:
  SavingJpeg();
  SavingJpeg(QOpenGLWidget* new_scene);
  ~SavingJpeg();

  void SaveModel() override;

 private:
  QOpenGLWidget* scene_;
};

};      // namespace viewer
#endif  // SRC_VIEW_SAVINGJPEG_H_
