#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <iostream>
#include <vector>

#include "MyGLWidget.h"
#include "SavingBmp.h"
#include "SavingJpeg.h"
#include "TypeSavingModel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace viewer {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

  void setShowData(const std::vector<double> &vertices,
                   const std::vector<unsigned int> &lines);
  void showFileDetails(QString &filename, int count_vertex, int count_edges);
  void UpdateViewParams();

  void reDraw();

  void closeEvent(QCloseEvent *event) override;

 signals:
  void handleOpenFile(QString &filepath);
  void handleMove(double x, double y, double z);
  void handleRotate(double x, double y, double z);
  void handleScale(double scale);

 private slots:
  void onSliderValueChangedMove();
  void onSliderValueChangedRotate();
  void onSliderValueChangedScale();

  void on_load_model_clicked();

  void onChangeVertexRendering();
  void onChangeEdgeRendering();
  void onChangeMainCanvaRendering();

  void on_choiseBGColor_clicked();
  void on_choiseEdgeColor_clicked();
  void on_choiseVertexColor_clicked();

  void on_reset_settings_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void TimeGif();

 private:
  void resetTransformButtons();
  void connectSignals();

  Ui::View *ui;

  std::vector<double> last_coordinates_;
  std::vector<double> last_rotation_;
  double last_scale_;

  QTimer *timer_;
  QGifImage *gifimage_;
  QImage *image_;
  int time_ = 0;
  bool user_interaction_;
};

}  // namespace viewer

#endif  // SRC_VIEW_VIEW_H_
