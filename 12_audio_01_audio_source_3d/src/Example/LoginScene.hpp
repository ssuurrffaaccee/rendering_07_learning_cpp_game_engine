#pragma once
#include <glm/glm.hpp>

#include "Engine/Component/Component.hpp"
#include "Engine/Control/Input.hpp"
using namespace std;

class Transform;
class Camera;
class Material;
class LoginScene : public Component {
 public:
  LoginScene();

  void Awake();

  void Update();

 private:
    /// 创建音源
    void CreateAudioSource();
    /// 创建听者
    void CreateAudioListener();

 private:
    Transform*      transform_camera_1_= nullptr;
    Camera*         camera_1_= nullptr;
    glm::vec2     last_frame_mouse_position_={0,0};//上一帧的鼠标位置

    Transform*      transform_player_= nullptr;
};
