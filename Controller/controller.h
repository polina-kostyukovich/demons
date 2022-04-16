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
  void SetView(const std::shared_ptr<View>& view);

  void Connect();

  const Hero& GetHero() const override;

  void StartTimer() override;

  void HandleKeyPressEvent(QKeyEvent* event) override;
  void HandleKeyReleaseEvent(QKeyEvent* event) override;

 public slots:
  void TimerTick();

 private:
  void ConnectTimer();
  Vector2D GetDirection() const;

 private:
  std::unique_ptr<Model> model_{nullptr};
  std::shared_ptr<View> view_{nullptr};
  QTimer* timer_{new QTimer(this)};
  std::map<int, bool> keys_;
};

#endif  // CONTROLLER_CONTROLLER_H_
