#include "controller.h"

#include <cassert>
#include <utility>

void Controller::SetModel(std::unique_ptr<Model>&& model) {
  assert(model != nullptr);
  model_ = std::move(model);
}

const Hero& Controller::GetHero() const {
  return model_->GetHero();
}
