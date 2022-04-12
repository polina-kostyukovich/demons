#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "../GameObject/hero.h"

class AbstractController {
 public:
  virtual const Hero& GetHero();
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
