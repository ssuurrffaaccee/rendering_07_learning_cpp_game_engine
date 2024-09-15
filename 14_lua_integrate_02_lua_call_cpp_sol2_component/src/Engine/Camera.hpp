#pragma once
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include "ToString.hpp"

#include "Component.hpp"

class Camera : public Component {
 public:
  ~Camera() {}

 public:
  void Awake() override { std::cout << "Camera Awake" << std::endl; }

  void Update() override {
      std::cout<<"Camera Update"<<std::endl;
  }

  void set_position(glm::vec3 position) {
    std::cout << "Camera set_position:" << to_string(position)
              << std::endl;
    position_ = position;
  }

  glm::vec3 position() { return position_; }

 private:
  glm::vec3 position_;
};
