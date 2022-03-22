#include <cassert>
#include "app.h"

App::App(const Model* model, const View* view, const Controller* controller) {
  if (is_running_) {
    assert(false);
  }

  model_ = std::make_unique<Model>(*model);
  view_ = std::make_unique<View>(*view);
  controller_ = std::make_unique<Controller>(*controller);
  is_running_ = true;
}

void App::Run() {
}
