#include <cassert>
#include <utility>

#include "app.h"

App::App(std::unique_ptr<Model>&& model,
         std::unique_ptr<View>&& view,
         std::unique_ptr<Controller>&& controller) {
  assert(model_ == nullptr && view_ == nullptr && controller_ == nullptr);

  model_ = std::move(model);
  view_ = std::move(view);
  controller_ = std::move(controller);
}

void App::Run() {
}

