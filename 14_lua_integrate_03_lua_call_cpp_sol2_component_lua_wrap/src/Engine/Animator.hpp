#pragma once
#include <iostream>
#include <rttr/registration>
#include "Component.hpp"


class Animator:public Component
{
public:
    Animator(): Component(){}
    ~Animator(){}
public:
    void Awake() override{
        std::cout<<"Cpp.Animator Awake"<<std::endl;
        Component::Awake();
    }

    void Update() override{
        std::cout<<"Cpp.Animator Update"<<std::endl;
        Component::Update();
    }

RTTR_ENABLE();
};