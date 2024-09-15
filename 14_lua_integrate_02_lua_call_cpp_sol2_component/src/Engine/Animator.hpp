#pragma once
#include <iostream>

#include "Component.hpp"

class Animator : public Component {
 public:
  ~Animator() {}

 public:
  void Awake() override { std::cout << "Animator Awake" << std::endl; }

  void Update() override {
      std::cout<<"Animator Update"<<std::endl;
  }
};