#ifndef APP_APP_H_
#define APP_APP_H_

#include <memory>

class App {
 public:
  App(std::unique_ptr<Model>&& model,
      std::unique_ptr<View>&& view,
      std::unique_ptr<Controller>&& controller);

  void Run();

 private:
  std::unique_ptr<Model> model_ = nullptr;
  std::unique_ptr<View> view_ = nullptr;
  std::unique_ptr<Controller> controller_ = nullptr;
};

#endif  // APP_APP_H_
