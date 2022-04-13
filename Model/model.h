#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include "../GameObject/hero.h"

class Model {
 public:
  const Hero& GetHero();

 private:
  Hero hero_;
};

#endif  // MODEL_MODEL_H_
