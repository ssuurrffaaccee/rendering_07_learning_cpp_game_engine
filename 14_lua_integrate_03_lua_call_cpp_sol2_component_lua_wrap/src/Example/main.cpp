#include "Engine/Animator.hpp"
#include "Engine/Camera.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/KeyAction.hpp"
#include "Engine/UI_Camera.hpp"
#include <functional>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <sol/sol.hpp>
#include <string>
#include "Engine/ToString.hpp"


sol::state sol_state;

void CompareGameObject(GameObject *a, GameObject *b) {
  std::cout << "CompareGameObject a==b: " << (a == b) << std::endl;
}

int main(int argc, char *argv[]) {
  sol_state.open_libraries(sol::lib::base, sol::lib::package,
                           sol::lib::coroutine, sol::lib::string, sol::lib::os,
                           sol::lib::math, sol::lib::table, sol::lib::debug,
                           sol::lib::bit32, sol::lib::io, sol::lib::utf8);

  // 绑定glm::vec3
  {
    auto glm_ns_table = sol_state["glm"].get_or_create<sol::table>();
    glm_ns_table.new_usertype<glm::vec3>(
        "vec3", sol::call_constructor,
        sol::constructors<glm::vec3(const float &, const float &,
                                    const float &)>(),
        "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z, "r",
        &glm::vec3::r, "g", &glm::vec3::g, "b", &glm::vec3::b,
        sol::meta_function::to_string,
        [](const glm::vec3 *vec) -> std::string {
          return to_string(*vec);
        },
        sol::meta_function::addition,
        [](const glm::vec3 *vec_a, const glm::vec3 *vec_b) {
          return (*vec_a) + (*vec_b);
        },
        sol::meta_function::subtraction,
        [](const glm::vec3 *vec_a, const glm::vec3 *vec_b) {
          return (*vec_a) - (*vec_b);
        },
        sol::meta_function::multiplication,
        [](const glm::vec3 *vec, const float a) { return (*vec) * a; },
        sol::meta_function::division,
        [](const glm::vec3 *vec, const float a) { return (*vec) / a; },
        sol::meta_function::unary_minus,
        [](const glm::vec3 *vec) { return (*vec) * -1.0f; },
        sol::meta_function::equal_to,
        [](const glm::vec3 *vec_a, const glm::vec3 *vec_b) {
          return (*vec_a) == (*vec_b);
        });
  }

  // 绑定glm::vec4
  {
    auto glm_ns_table = sol_state["glm"].get_or_create<sol::table>();
    glm_ns_table.new_usertype<glm::vec4>(
        "vec4", sol::call_constructor,
        sol::constructors<glm::vec4(const float &, const float &, const float &,
                                    const float &)>(),
        "x", &glm::vec4::x, "y", &glm::vec4::y, "z", &glm::vec4::z, "w",
        &glm::vec4::w, "r", &glm::vec4::r, "g", &glm::vec4::g, "b",
        &glm::vec4::b, "a", &glm::vec4::a, sol::meta_function::to_string,
        [](const glm::vec4 *vec) { return to_string(*vec); },
        sol::meta_function::addition,
        [](const glm::vec4 *vec_a, const glm::vec4 *vec_b) {
          return (*vec_a) + (*vec_b);
        },
        sol::meta_function::subtraction,
        [](const glm::vec4 *vec_a, const glm::vec4 *vec_b) {
          return (*vec_a) - (*vec_b);
        },
        sol::meta_function::multiplication,
        [](const glm::vec4 *vec, const float a) { return (*vec) * a; },
        sol::meta_function::division,
        [](const glm::vec4 *vec, const float a) { return (*vec) / a; },
        sol::meta_function::unary_minus,
        [](const glm::vec4 *vec) { return (*vec) * -1.0f; },
        sol::meta_function::equal_to,
        [](const glm::vec4 *vec_a, const glm::vec4 *vec_b) {
          return (*vec_a) == (*vec_b);
        });
  }

  // 绑定glm::mat4
  {
    auto glm_ns_table = sol_state["glm"].get_or_create<sol::table>();
    glm_ns_table.new_usertype<glm::mat4>(
        "mat4", sol::call_constructor,
        sol::constructors<glm::mat4(const float &)>(),
        sol::meta_function::to_string,
        [](const glm::mat4 *m) { return to_string(*m); },
        sol::meta_function::addition,
        [](const glm::mat4 *m_a, const glm::mat4 *m_b) {
          return (*m_a) + (*m_b);
        },
        sol::meta_function::subtraction,
        [](const glm::mat4 *m_a, const glm::mat4 *m_b) {
          return (*m_a) - (*m_b);
        },
        sol::meta_function::multiplication,
        [](const glm::mat4 *m, const glm::vec4 *v) { return (*m) * (*v); },
        sol::meta_function::division,
        [](const glm::mat4 *m, const float a) { return (*m) / a; },
        sol::meta_function::unary_minus,
        [](const glm::mat4 *m) { return (*m) * -1.0f; },
        sol::meta_function::equal_to,
        [](const glm::mat4 *m_a, const glm::mat4 *m_b) {
          return (*m_a) == (*m_b);
        });
  }

  // 绑定glm函数
  {
    auto glm_ns_table = sol_state["glm"].get_or_create<sol::table>();
    glm_ns_table.set_function(
        "rotate", sol::overload([](const glm::mat4 *m, const float f,
                                   const glm::vec3 *v) {
          return glm::rotate(*m, f, *v);
        }));
    glm_ns_table.set_function("radians", sol::overload([](const float f) {
                                return glm::radians(f);
                              }));
    glm_ns_table.set_function(
        "to_string",
        sol::overload([](const glm::mat4 *m) { return to_string((*m)); },
                      [](const glm::vec3 *v) { return to_string((*v)); }));
  }

  auto cpp_ns_table = sol_state["Cpp"].get_or_create<sol::table>();
  // 绑定 GameObject
  {
    cpp_ns_table.new_usertype<GameObject>(
        "GameObject", sol::call_constructor, sol::constructors<GameObject()>(),
        "AttachComponent", &GameObject::AttachComponent);
  }

  // 绑定 Component
  {
    cpp_ns_table.new_usertype<Component>(
        "Component", sol::call_constructor, sol::constructors<Component()>(),
        "Awake", &Component::Awake, "Update", &Component::Update, "game_object",
        &Component::game_object, "set_game_object", &Component::set_game_object,
        "set_lua_component_instance", &Component::set_lua_component_instance);
  }

  // 绑定 Animator
  {
    cpp_ns_table.new_usertype<Animator>(
        "Animator", sol::call_constructor, sol::constructors<Animator()>(),
        sol::base_classes, sol::bases<Component>());
  }
  // 绑定 Camera
  {
    cpp_ns_table.new_usertype<Camera>(
        "Camera", sol::call_constructor, sol::constructors<Camera()>(),
        sol::base_classes, sol::bases<Component>(), "position",
        &Camera::position, "set_position", &Camera::set_position);
    cpp_ns_table.new_usertype<UICamera>(
        "UICamera", sol::call_constructor, sol::constructors<UICamera()>(),
        sol::base_classes, sol::bases<Camera, Component>());
  }

  // 绑定普通函数
  { cpp_ns_table.set_function("CompareGameObject", &CompareGameObject); }

  // 绑定常量
  {
    const int const_value = 12;

    auto test_ns_table = sol_state["Test"].get_or_create<sol::table>();
    test_ns_table.set("const_value", const_value);
  }

  // 绑定枚举
  {
    cpp_ns_table.new_enum<KeyAction, true>(
        "KeyAction", {{"UP", KeyAction::UP}, {"DOWN", KeyAction::DOWN}});

    cpp_ns_table.set_function("GetKeyActionUp", &GetKeyActionUp);
    cpp_ns_table.set_function("GetKeyActionDown", &GetKeyActionDown);
  }

  // 设置lua搜索目录
  {
    sol::table package_table = sol_state["package"];
    std::string path = package_table["path"];
    path.append(";./lua/?.lua;");
    package_table["path"] = path;
  }

  // 执行lua
  auto result = sol_state.script_file("../src/Example/lua/main.lua");
  if (result.valid() == false) {
    sol::error err = result;
    std::cerr << "---- LOAD LUA ERROR ----" << std::endl;
    std::cerr << err.what() << std::endl;
    std::cerr << "------------------------" << std::endl;
  }

  // 调用lua main()
  sol::protected_function main_function = sol_state["main"];
  result = main_function();
  if (result.valid() == false) {
    sol::error err = result;
    std::cerr << "----- RUN LUA ERROR ----" << std::endl;
    std::cerr << err.what() << std::endl;
    std::cerr << "------------------------" << std::endl;
  }

  for (int i = 0; i < 5; i++) {
    std::cout << "Loop " << i << std::endl;

    GameObject::Foreach([](GameObject *game_object) {
      std::cout<<"xxxxx\n";
      game_object->ForeachComponent(
          [](Component *component) { component->Update(); });
    });
  }

  return 0;
}
