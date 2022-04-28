#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <QKeyEvent>
#include <QObject>

#include "../GameObject/hero.h"
#include "../Map/map.h"

class AbstractController : public QObject {
  Q_OBJECT
 public:
  virtual void StartNewGame() = 0;
  virtual void ContinueGame() = 0;

  virtual void ChangeLanguage(int language_number) = 0;
  virtual void ChangeSoundOn() = 0;

  virtual const Hero& GetHero() const = 0;
  virtual const Map& GetMap() const = 0;
  virtual int GetCounter() const = 0;

  virtual void HandleKeyPressEvent(QKeyEvent* event) = 0;
  virtual void HandleKeyReleaseEvent(QKeyEvent* event) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
