#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QTimer>
#include <QKeyEvent>
// #include <QTimerEvent>
#include <QWidget>

#include "abstract_controller.h"
#include "../Model/model.h"

class Controller : public QWidget, public AbstractController {
  Q_OBJECT
 public:
  Controller(std::unique_ptr<Model>&& model);

  void TimerTick();
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:
  std::unique_ptr<Model> model_;
  QTimer* timer_;
};

#endif  // CONTROLLER_CONTROLLER_H_
