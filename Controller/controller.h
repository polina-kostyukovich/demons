#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <map>
#include <memory>
#include <QKeyEvent>
#include <QTimer>
#include <QWidget>

#include "abstract_controller.h"
#include "../Model/model.h"

class Controller : public AbstractController {
 public:
  Controller() = default;

  void SetModel(std::unique_ptr<Model>&& model);

  const Hero& GetHero() const override;

  void TimerTick();
  void HandleKeyPressEvent(QKeyEvent* event) override;
  void HandleKeyReleaseEvent(QKeyEvent* event) override;

 private:
  Vector2D GetDirection() const;

 private:
  std::unique_ptr<Model> model_ = nullptr;
  std::unique_ptr<QTimer> timer_;
  std::map<int, bool> keys_;
};

#endif  // CONTROLLER_CONTROLLER_H_
