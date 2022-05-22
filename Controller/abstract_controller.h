#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <memory>
#include <QKeyEvent>
#include <QObject>

#include "../GameObject/hero.h"
#include "../Map/map.h"
#include "../Model/model.h"
#include "../Util/structs.h"

class AbstractController : public QObject {
  Q_OBJECT
 public:
  virtual void WriteSettings() = 0;

  virtual const Model& GetModel() const = 0;

  virtual void StartGame() = 0;
  virtual void NewGame() = 0;

  virtual void ChangeLanguage(Language language) = 0;
  virtual void ChangeSoundOn() = 0;

  virtual int GetCounter() const = 0;

  virtual bool IsSoundOn() const = 0;

  virtual void HandleKeyPressEvent(QKeyEvent* event) = 0;
  virtual void HandleKeyReleaseEvent(QKeyEvent* event) = 0;

  virtual void HandleMousePressEvent(QMouseEvent* event) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
