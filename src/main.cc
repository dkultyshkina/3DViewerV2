#include <QApplication>

#include "Controller/Controller.h"
#include "Model/Facade.h"
#include "View/View.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_NUMERIC, "C");
  viewer::View view;
  viewer::Facade model;
  viewer::Controller controller(view, model);

  view.show();
  return a.exec();
}
