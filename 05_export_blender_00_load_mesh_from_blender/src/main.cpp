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

  MeshFilter* mesh_filter = new MeshFilter();
  mesh_filter->LoadMesh("model/fishsoup_pot.mesh");

  Material* material = new Material();
  material->Parse("material/fishsoup_pot.mat");

  MeshRenderer* mesh_renderer = new MeshRenderer();
  mesh_renderer->SetMeshFilter(mesh_filter);
  mesh_renderer->SetMaterial(material);

  while (!glfwWindowShouldClose(window)) {
    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

    glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0));  // 不移动顶点坐标;

    static float rotate_eulerAngle = 0.f;
    rotate_eulerAngle += 0.1f;
    glm::mat4 rotation = glm::eulerAngleYXZ(
        glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle),
        glm::radians(rotate_eulerAngle));  // 使用欧拉角旋转;

    glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));  // 缩放;
    glm::mat4 model = trans * scale * rotation;
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));
    glm::mat4 projection =
        glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);
    glm::mat4 mvp = projection * view * model;

    mesh_renderer->SetMVP(mvp);
    mesh_renderer->Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}