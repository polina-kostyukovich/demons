#include "controller.h"

#include <cassert>
#include <utility>

Controller::Controller(std::unique_ptr<Model>&& model) {
  model_ = std::move(model);
}

const Hero& Controller::GetHero() {
  return model_->GetHero();
}
