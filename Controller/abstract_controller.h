#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "../GameObject/hero.h"

class AbstractController {
 public:
  virtual const Hero& GetHero() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
