#ifndef APP_APP_H_
#define APP_APP_H_

#include <memory>

#include "../Controller/controller.h"
#include "../Model/model.h"
#include "../View/view.h"

class App {
 public:
  App(std::unique_ptr<Model>&& model,
      std::unique_ptr<Controller>&& controller,
      std::unique_ptr<View>&& view);
  void Run();

 private:
  std::unique_ptr<View> view_;
};

#endif  // APP_APP_H_
