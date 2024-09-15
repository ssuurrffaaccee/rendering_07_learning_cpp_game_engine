#pragma once
#include "Engine/Component/Component.hpp"
#include "Engine/Control/Input.hpp"

using namespace std;

class Transform;
class Camera;
class LoginScene:public Component{
public:
    LoginScene();

    void Awake();

    void Update();

private:
    Transform* transform_fishsoup_pot_;
    Transform* transform_camera_1_;
    Camera*     camera_1_;
    Transform* transform_camera_2_;
    Camera*     camera_2_;
    vec2_ushort last_frame_mouse_position_;//上一帧的鼠标位置
};