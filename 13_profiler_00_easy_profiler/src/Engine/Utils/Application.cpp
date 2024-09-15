#include "Engine/Utils/Application.hpp"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
#include <easy/profiler.h>
#include "Engine/Component/GameObject.hpp"
#include "Engine/Control/Input.hpp"
#include "Engine/RenderDevice/RenderDevice_OpenGL.hpp"
#include "Engine/Renderer/Camera.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Utils/Debug.hpp"
#include "Engine/Utils/Screen.hpp"
#include "Engine/Audio/Audio.hpp"
#include "Engine/Utils/Time.hpp"

std::string Application::data_path_;
GLFWwindow* Application::glfw_window_;

static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

/// 键盘回调
/// \param window
/// \param key
/// \param scancode
/// \param action
/// \param mods
static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
  Input::RecordKey(key, action);
}
/// 鼠标按键回调
/// \param window
/// \param button
/// \param action
/// \param mods
static void mouse_button_callback(GLFWwindow* window, int button, int action,
                                  int mods) {
  Input::RecordKey(button, action);
  //    std::cout<<"mouse_button_callback:"<<button<<","<<action<<std::endl;
}
/// 鼠标移动回调
/// \param window
/// \param x
/// \param y
static void mouse_move_callback(GLFWwindow* window, double x, double y) {
  Input::set_mousePosition(x, y);
  //    std::cout<<"mouse_move_callback:"<<x<<","<<y<<std::endl;
}
/// 鼠标滚轮回调
/// \param window
/// \param x
/// \param y
static void mouse_scroll_callback(GLFWwindow* window, double x, double y) {
  Input::RecordScroll(y);
  //    std::cout<<"mouse_scroll_callback:"<<x<<","<<y<<std::endl;
}

void Application::Init() {
  EASY_MAIN_THREAD;
  profiler::startListen();// 启动profiler服务器，等待gui连接。
  // EASY_PROFILER_ENABLE;
  // profiler::dumpBlocksToFile("./test_profile.prof");
  Debug::Init();
  DEBUG_LOG_INFO("game start");
  Time::Init();
  RenderDevice::Init(new RenderDeviceOpenGL());

  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    DEBUG_LOG_ERROR("glfw init failed!");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfw_window_ = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
  if (!glfw_window_) {
    DEBUG_LOG_ERROR("glfwCreateWindow error!");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(glfw_window_);
  // gladLoadGL(glfwGetProcAddress);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  UpdateScreenSize();
  glfwSwapInterval(1);

  glfwSetKeyCallback(glfw_window_, key_callback);
  glfwSetMouseButtonCallback(glfw_window_, mouse_button_callback);
  glfwSetScrollCallback(glfw_window_, mouse_scroll_callback);
  glfwSetCursorPosCallback(glfw_window_, mouse_move_callback);

  //初始化 fmod
  Audio::Init();
}

void Application::Update() {
  EASY_FUNCTION(profiler::colors::Magenta); // 标记函数
  Time::Update();
  UpdateScreenSize();

  GameObject::Foreach([](GameObject* game_object) {
    if (game_object->active()) {
      game_object->ForeachComponent(
          [](Component* component) { component->Update(); });
    }
  });

  Input::Update();
  Audio::Update();
}

void Application::Render() {
  EASY_FUNCTION(profiler::colors::Magenta); // 标记函数
  // 遍历所有相机，每个相机的View Projection，都用来做一次渲染。
  Camera::Foreach([&]() {
    GameObject::Foreach(
        [](GameObject* game_object) {  // tree post order traversal
          if (game_object->active() == false) {
            return;
          }
          auto component = game_object->GetComponent("MeshRenderer");
          if (!component) {
            return;
          }
          auto mesh_renderer = dynamic_cast<MeshRenderer*>(component);
          if (!mesh_renderer) {
            return;
          }
          mesh_renderer->Render();
        });
  });
}

void Application::Run() {
    while (true)
    {
        EASY_BLOCK("Frame"){
            if(glfwWindowShouldClose(glfw_window_)){
                break;
            }
            Update();
            Render();

            EASY_BLOCK("glfwSwapBuffers"){
                glfwSwapBuffers(glfw_window_);
            }
            EASY_END_BLOCK;

            EASY_BLOCK("glfwPollEvents"){
                glfwPollEvents();
            }
            EASY_END_BLOCK;
        }EASY_END_BLOCK;
    }

    glfwDestroyWindow(glfw_window_);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::UpdateScreenSize() {
  int view_port_width, view_port_height;
  glfwGetFramebufferSize(glfw_window_, &view_port_width, &view_port_height);
  glViewport(0, 0, view_port_width, view_port_height);

  int window_width, window_height;
  glfwGetWindowSize(glfw_window_, &window_width, &window_height);
  Screen::set_width_height(window_width, window_height);
}