#include <glad/glad.h>

#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform2.hpp>

#include "Component/GameObject.hpp"
#include "Component/Transform.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/MeshFilter.hpp"
#include "Renderer/MeshRenderer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture2D.hpp"
#include "Utils/Application.hpp"

static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;

// 初始化OpenGL
void init_opengl() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  // gladLoadGL(glfwGetProcAddress);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(1);
}

int main(void) {
  Application::set_data_path("../../resources/");
  init_opengl();

  // 创建模型 GameObject
  GameObject* go = new GameObject("something");

  // 挂上 Transform 组件
  auto transform = dynamic_cast<Transform*>(go->AddComponent("Transform"));

  // 挂上 MeshFilter 组件
  auto mesh_filter = dynamic_cast<MeshFilter*>(go->AddComponent("MeshFilter"));
  mesh_filter->LoadMesh("model/fishsoup_pot.mesh");

  // 挂上 MeshRenderer 组件
  auto mesh_renderer =
      dynamic_cast<MeshRenderer*>(go->AddComponent("MeshRenderer"));
  Material* material = new Material();  // 设置材质
  material->Parse("material/fishsoup_pot.mat");
  mesh_renderer->SetMaterial(material);

  // 创建相机 GameObject
  auto go_camera = new GameObject("main_camera");
  // 挂上 Transform 组件
  auto transform_camera =
      dynamic_cast<Transform*>(go_camera->AddComponent("Transform"));
  transform_camera->set_position(glm::vec3(0, 0, 10));
  // 挂上 Camera 组件
  auto camera = dynamic_cast<Camera*>(go_camera->AddComponent("Camera"));

  while (!glfwWindowShouldClose(window)) {
    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    ratio = width / (float)height;

    // 设置相机
    camera->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    camera->SetProjection(60.f, ratio, 1.f, 1000.f);
    camera->Clear();

    // 旋转物体
    static float rotate_eulerAngle = 0.f;
    rotate_eulerAngle += 0.1f;
    glm::vec3 rotation = transform->rotation();
    rotation.y = rotate_eulerAngle;
    transform->set_rotation(rotation);

    mesh_renderer->SetView(camera->view_mat4());
    mesh_renderer->SetProjection(camera->projection_mat4());
    mesh_renderer->Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}