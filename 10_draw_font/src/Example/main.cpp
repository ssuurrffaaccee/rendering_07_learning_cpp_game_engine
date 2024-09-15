

#include "Engine/Component/GameObject.hpp"
#include "Engine/Utils/Application.hpp"

int main(void) {
  Application::set_data_path("../../resources/");  // 设置资源目录
  Application::InitOpengl();                       // 初始化引擎

  GameObject* go = new GameObject("LoginSceneGo");
  go->AddComponent("Transform");
  go->AddComponent("LoginScene");
  Application::Run();  // 开始引擎主循环
  return 0;
}