/*!
\file
\brief Исходный файл SavingModelStrategy.h

Данный файл содержит в себе описание класса SavingModelStrategy и его
виртуальный метод
*/

#ifndef SRC_VIEW_SAVINGMODELSTRATEGY_H_
#define SRC_VIEW_SAVINGMODELSTRATEGY_H_

#include <QObject>
#include <iostream>

namespace viewer {

class SavingModelStrategy : public QObject {
 public:
  virtual ~SavingModelStrategy() = default;
  virtual void SaveModel() = 0;
};

};      // namespace viewer
#endif  // SRC_VIEW_SAVINGMODELSTRATEGY_H_
