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

  void Start();

  void StartGame() override;
  void NewGame() override;
  void Pause();

  void ChangeLanguage(Language language) override;
  void ChangeSoundOn() override;

  const Hero& GetHero() const override;
  const Map& GetMap() const override;

  void HandleKeyPressEvent(QKeyEvent* event) override;
  void HandleKeyReleaseEvent(QKeyEvent* event) override;

  int GetCounter() const override;

 public slots:
  void TimerTick();

 private:
  Vector2D GetHeroDirection() const;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;
  QTimer* timer_{new QTimer(this)};
  std::map<int, bool> keys_;
  int counter_{0};
};

#endif  // CONTROLLER_CONTROLLER_H_
