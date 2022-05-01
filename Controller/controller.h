#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <map>
#include <memory>
#include <QKeyEvent>
#include <QTimer>
#include <QWidget>

#include "abstract_controller.h"
#include "../Model/model.h"
#include "../View/view.h"

class Controller : public AbstractController {
 public:
  Controller() = default;

  void SetModel(std::unique_ptr<Model>&& model);
  void SetView(std::unique_ptr<View>&& view);

  void ConnectTimer();

  const Hero& GetHero() const override;
  const Map& GetMap() const override;

  void Start();

  void HandleKeyPressEvent(QKeyEvent* event) override;
  void HandleKeyReleaseEvent(QKeyEvent* event) override;

  int GetCounter() const override;

  const std::unique_ptr<Model>& GetModel() const override;

  void HandleMousePressEvent(QMouseEvent* event,
                             const Point& mouse_pos) override;
  void HandleMouseReleaseEvent(QMouseEvent* event) override;

 public slots:
  void TimerTick();

 private:
  Vector2D GetDirection() const;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;
  QTimer* timer_{new QTimer(this)};
  std::map<int, bool> keys_;
  int counter_{0};
  bool is_clicked{false};
};

#endif  // CONTROLLER_CONTROLLER_H_
