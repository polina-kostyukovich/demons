#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <QKeyEvent>
#include <QObject>

#include "../GameObject/hero.h"
#include "../Map/map.h"
#include "../Util/structs.h"

class AbstractController : public QObject {
  Q_OBJECT
 public:
  virtual void StartGame() = 0;
  virtual void NewGame() = 0;

  virtual void ChangeLanguage(Language language) = 0;
  virtual void ChangeSoundOn() = 0;

  virtual const Hero& GetHero() const = 0;
  virtual const Map& GetMap() const = 0;
  virtual int GetCounter() const = 0;

  virtual void HandleKeyPressEvent(QKeyEvent* event) = 0;
  virtual void HandleKeyReleaseEvent(QKeyEvent* event) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
