#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <map>
#include <memory>
#include <QKeyEvent>
#include <QTimer>
#include <QWidget>

#include "abstract_controller.h"
#include "../Model/model.h"

class Controller : public QWidget, public AbstractController {
  Q_OBJECT
 public:
  explicit Controller(std::unique_ptr<Model>&& model);

  void TimerTick();
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:
  Vector2D GetDirection() const;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<QTimer> timer_;
  std::map<int, bool> keys_;
};

#endif  // CONTROLLER_CONTROLLER_H_
