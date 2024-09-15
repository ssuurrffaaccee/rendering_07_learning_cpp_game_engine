#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <rttr/registration>
#include "Component.hpp"
#include "ToString.hpp"
using namespace rttr;

class Camera:public Component
{
public:
    Camera(): Component(){}
    ~Camera(){}
public:
    void Awake() override{
        std::cout<<"Cpp.Camera Awake"<<std::endl;
        Component::Awake();
    }

    void Update() override{
        std::cout<<"Cpp.Camera Update"<<std::endl;
        Component::Update();
    }

    void set_position(glm::vec3 position){
        std::cout<<"Cpp.Camera set_position:"<<to_string(position)<<std::endl;
        position_=position;
    }

    glm::vec3 position(){
        return position_;
    }

private:
    glm::vec3 position_;

RTTR_ENABLE();
};