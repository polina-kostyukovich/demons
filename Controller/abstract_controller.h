#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <QKeyEvent>
#include <QObject>

class AbstractController : public QObject {
  Q_OBJECT
 public:
  virtual void HandleKeyPressEvent(QKeyEvent* event) = 0;
  virtual void HandleKeyReleaseEvent(QKeyEvent* event) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
