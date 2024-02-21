#include "View.h"

#include "ui_View.h"

namespace viewer {

View::View(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::View),
      last_coordinates_(3),
      last_rotation_(3),
      user_interaction_(true) {
  ui->setupUi(this);

  last_coordinates_[0] = ui->move_x->value();
  last_coordinates_[1] = ui->move_y->value();
  last_coordinates_[2] = ui->move_z->value();

  last_rotation_[0] = ui->rotate_x->value();
  last_rotation_[1] = ui->rotate_y->value();
  last_rotation_[2] = ui->rotate_z->value();

  last_scale_ = ui->scale_slider->value();

  connectSignals();
  ui->myGLWidget->LoadSettings();
  UpdateViewParams();
}

void View::resetTransformButtons() {
  user_interaction_ = false;

  // Смещения
  ui->move_x->setValue(0);
  ui->move_y->setValue(0);
  ui->move_z->setValue(0);
  // Сбросить значения смещения для обработчика смещения
  last_coordinates_ = {0, 0, 0};

  // Вращения
  ui->rotate_x->setValue(0);
  ui->rotate_y->setValue(0);
  ui->rotate_z->setValue(0);
  // Сбросить значения поворота для обработчика смещения
  last_rotation_ = {0, 0, 0};

  // Масштабирования
  ui->scale_slider->setValue(100);
  // Сбросить значения для обработчика масштабирования
  last_scale_ = 100;

  user_interaction_ = true;
}

void View::connectSignals() {
  // Отслеживание смещений
  connect(ui->move_x, &QSlider::valueChanged, this,
          &View::onSliderValueChangedMove);
  connect(ui->move_y, &QSlider::valueChanged, this,
          &View::onSliderValueChangedMove);
  connect(ui->move_z, &QSlider::valueChanged, this,
          &View::onSliderValueChangedMove);

  // Отслеживание вращения
  connect(ui->rotate_x, &QSlider::valueChanged, this,
          &View::onSliderValueChangedRotate);
  connect(ui->rotate_y, &QSlider::valueChanged, this,
          &View::onSliderValueChangedRotate);
  connect(ui->rotate_z, &QSlider::valueChanged, this,
          &View::onSliderValueChangedRotate);

  // Отслеживание массштабирования
  connect(ui->scale_slider, &QSlider::valueChanged, this,
          &View::onSliderValueChangedScale);

  // Отслеживание изменение параметров отрисовки вершин
  connect(ui->vertex_size, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &View::onChangeVertexRendering);
  connect(ui->vertex_type, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &View::onChangeVertexRendering);

  // Отслеживание изменение параметров отрисовки границ
  connect(ui->edge_size, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &View::onChangeEdgeRendering);
  connect(ui->edge_type, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &View::onChangeEdgeRendering);

  connect(ui->comboBoxProjection,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &View::onChangeMainCanvaRendering);
}

View::~View() { delete ui; }

void View::reDraw() {
  ui->myGLWidget->reDraw();
  update();
}

void View::closeEvent(QCloseEvent *event) {
  ui->myGLWidget->SaveSettings();
  QMainWindow::closeEvent(event);
}

void View::setShowData(const std::vector<double> &vertices,
                       const std::vector<unsigned int> &lines) {
  ui->myGLWidget->SetDrawData(vertices, lines);
  resetTransformButtons();
  reDraw();
}

void View::showFileDetails(QString &filename, int count_vertex,
                           int count_edges) {
  QString status = "Vertexes = " + QString::number(count_vertex) +
                   ";\tEdges = " + QString::number(count_edges) +
                   ";\t\tFile path=\"" + filename + "\"";
  ui->statusbar->showMessage(status);
}

void View::UpdateViewParams() {
  user_interaction_ = false;
  MyGLWidget *gl_widget_ = ui->myGLWidget;
  // Canva params
  ui->comboBoxProjection->setCurrentIndex(
      static_cast<int>(gl_widget_->GetCanvaProjection()));

  // Vertex params
  ui->vertex_size->setValue(gl_widget_->GetVertexSize());
  ui->vertex_type->setCurrentIndex(
      static_cast<int>(gl_widget_->GetVertexType()));

  // Edge params
  ui->edge_type->setCurrentIndex(static_cast<int>(gl_widget_->GetEdgeType()));
  ui->edge_size->setValue(gl_widget_->GetEdgeSize());

  user_interaction_ = true;
  reDraw();
}

void View::onChangeVertexRendering() {
  if (!user_interaction_) {
    return;
  }

  double size = ui->vertex_size->value();
  ui->myGLWidget->SetVertexSize(size);

  int current_index = ui->vertex_type->currentIndex();
  if (current_index == 0) {
    ui->myGLWidget->SetVertexType(
        VertexSetting::VertexSetting::VertexType::kNone);
  } else if (current_index == 1) {
    ui->myGLWidget->SetVertexType(
        VertexSetting::VertexSetting::VertexType::kRounded);
  } else if (current_index == 2) {
    ui->myGLWidget->SetVertexType(
        VertexSetting::VertexSetting::VertexType::kSquare);
  }

  reDraw();
}

void View::onChangeEdgeRendering() {
  if (!user_interaction_) {
    return;
  }

  int size = ui->edge_size->value();
  ui->myGLWidget->SetEdgeSize(size);

  int current_index = ui->edge_type->currentIndex();
  if (current_index == 0) {
    ui->myGLWidget->SetEdgeType(EdgeSetting::EdgeType::kSolid);
  } else if (current_index == 1) {
    ui->myGLWidget->SetEdgeType(EdgeSetting::EdgeType::kDotted);
  }

  reDraw();
}

void View::onChangeMainCanvaRendering() {
  if (!user_interaction_) {
    return;
  }
  int current_index = ui->comboBoxProjection->currentIndex();
  if (current_index == 0) {
    ui->myGLWidget->SetCanvaProjection(CanvaSetting::ProjectionType::kParalel);
  } else if (current_index == 1) {
    ui->myGLWidget->SetCanvaProjection(CanvaSetting::ProjectionType::kCentral);
  }

  reDraw();
}

void View::onSliderValueChangedMove() {
  if (!user_interaction_) {
    return;
  }
  double dx = (ui->move_x->value() - last_coordinates_[0]) / 100.0;
  double dy = (ui->move_y->value() - last_coordinates_[1]) / 100.0;
  double dz = (ui->move_z->value() - last_coordinates_[2]) / 100.0;

  last_coordinates_[0] = ui->move_x->value();
  last_coordinates_[1] = ui->move_y->value();
  last_coordinates_[2] = ui->move_z->value();

  // Отправляем сигнал с новыми значениями
  emit handleMove(dx, dy, dz);
}

void View::onSliderValueChangedScale() {
  if (!user_interaction_) {
    return;
  }
  double dvalue = ui->scale_slider->value() / last_scale_;
  last_scale_ = ui->scale_slider->value();

  // Отправляем сигнал с новыми значениями
  emit handleScale(dvalue);
}

void View::onSliderValueChangedRotate() {
  if (!user_interaction_) {
    return;
  }
  double x = ui->rotate_x->value() - last_rotation_[0];
  double y = ui->rotate_y->value() - last_rotation_[1];
  double z = ui->rotate_z->value() - last_rotation_[2];

  last_rotation_[0] = ui->rotate_x->value();
  last_rotation_[1] = ui->rotate_y->value();
  last_rotation_[2] = ui->rotate_z->value();

  // Отправляем сигнал с новыми значениями
  emit handleRotate(x, y, z);
}

void View::on_load_model_clicked() {
  QString file_name =
      QFileDialog::getOpenFileName(this, tr("Open obj file"), "",
                                   tr("obj files (*.obj) ;; All files (*.*)"));

  if (!file_name.isEmpty()) {
    std::cerr << "Open file: " << file_name.toStdString() << "\n";
    emit handleOpenFile(file_name);
  }
  UpdateViewParams();
}

void View::on_choiseBGColor_clicked() {
  ui->myGLWidget->SetCanvaBGColor(
      QColorDialog::getColor(Qt::black, this, tr("Select Color")));
  reDraw();
}

void View::on_choiseEdgeColor_clicked() {
  ui->myGLWidget->SetEdgeColor(
      QColorDialog::getColor(Qt::white, this, tr("Select Color")));
  reDraw();
}

void View::on_choiseVertexColor_clicked() {
  ui->myGLWidget->SetVertexColor(
      QColorDialog::getColor(Qt::white, this, tr("Select Color")));
  reDraw();
}

void View::on_reset_settings_clicked() {
  ui->myGLWidget->SetDefaultSettings();
  UpdateViewParams();
}

void View::on_pushButton_2_clicked() {
  try {
    if (ui->comboBox_2->currentText() == ".bmp") {
      TypeSavingModel type(new SavingBmp(ui->myGLWidget));
      type.SaveModel();
    } else {
      TypeSavingModel type(new SavingJpeg(ui->myGLWidget));
      type.SaveModel();
    }
    QMessageBox::information(this, "Information about success",
                             "Process of saving is successed!");
  } catch (std::string error) {
    QMessageBox::critical(this, "Error", "Process of saving is failed");
  }
}

void View::on_pushButton_3_clicked() {
  time_ = 0;
  timer_ = new QTimer();
  image_ = new QImage[50]{};
  connect(timer_, SIGNAL(timeout()), this, SLOT(TimeGif()));
  timer_->start(100);
}

void View::TimeGif() {
  if (time_ < 50) {
    image_[time_] = ui->myGLWidget->grab().toImage();
    ++time_;
  } else {
    gifimage_ = new QGifImage;
    for (int i = 0; i < time_; i++) {
      gifimage_->addFrame(image_[i], 0);
    }
    QString base_filename = "animation.gif";
    QString save_in_file = QFileDialog::getSaveFileName(
        this, "Save your record in file .gif:",
        QDir::currentPath() + "/" + base_filename, "GIF File (*.gif)");
    QFile file(save_in_file);
    if (!file.open(QIODevice::WriteOnly) || save_in_file.isEmpty()) {
      QMessageBox::critical(this, "Error", "Process of saving is failed");
    } else {
      bool result = gifimage_->save(save_in_file);
      if (result == false) {
        QMessageBox::critical(this, "Error", "Process of saving is failed");
      } else {
        QMessageBox::information(this, "Information about success",
                                 "Process of saving is successed!");
      }
    }
    timer_->stop();
    delete gifimage_;
    delete[] image_;
    time_ = 0;
  }
}

}  // namespace viewer
