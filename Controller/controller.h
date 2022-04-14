#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <memory>

#include "abstract_controller.h"
#include "../Model/model.h"

class Controller : public AbstractController {
 public:
  explicit Controller(std::unique_ptr<Model>&& model);

  const Hero& GetHero() const override;
 private:
  std::unique_ptr<Model> model_;
};

#endif  // CONTROLLER_CONTROLLER_H_
