#ifndef APP_APP_H_
#define APP_APP_H_

#include <memory>

class App {
 public:
  App(const Model* model, const View* view, const Controller* controller);

  void Run();

 private:
  std::unique_ptr<Model> model_ = nullptr;
  std::unique_ptr<View> view_ = nullptr;
  std::unique_ptr<Controller> controller_ = nullptr;
  inline static bool is_running_ = false;
};

#endif  // APP_APP_H_
