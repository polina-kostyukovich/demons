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
  void SetView(std::unique_ptr<View>&& view);

  void ConnectTimer();

  void StartNewGame() override;
  void ContinueGame() override;
  void StartGame();

  void ChangeLanguage(int language_number) override;
  void ChangeSoundOn() override;

  const Hero& GetHero() const override;

  void Start();

  void HandleKeyPressEvent(QKeyEvent* event) override;
  void HandleKeyReleaseEvent(QKeyEvent* event) override;

 public slots:
  void TimerTick();

 private:
  Vector2D GetDirection() const;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;
  QTimer* timer_{new QTimer(this)};
  std::map<int, bool> keys_;
};

#endif  // CONTROLLER_CONTROLLER_H_
