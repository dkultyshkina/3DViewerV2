#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <QMetaObject>
#include <QObject>
#include <vector>

#include "../Model/Facade.h"
#include "../View/View.h"

namespace viewer {

class Controller : public QObject {
  Q_OBJECT
 public:
  Controller(viewer::View& view, viewer::Facade& model);

 private slots:
  void ProcLoadFile(QString filepath);
  void ProcMoveModel(double x, double y, double z);
  void ProcRotateModel(double x, double y, double z);
  void ProcScaleModel(double coef);

 private:
  viewer::View& view_;
  viewer::Facade& model_;
};

}  // namespace viewer

#endif  // SRC_CONTROLLER_CONTROLLER_H_
