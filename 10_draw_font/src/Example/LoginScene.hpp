#pragma once
#include "Engine/Component/Component.hpp"
#include "Engine/Control/Input.hpp"

using namespace std;

class Transform;
class Camera;

class Transform;
class Camera;
class Material;
class LoginScene : public Component {
 public:
  LoginScene();

  void Awake();

  void Update();

 private:
  /// 创建鱼缸
  void CreateFishSoupPot();

  /// 创建文字
  void CreateFont();

 private:
  Transform* transform_fishsoup_pot_;
  //    Material* material;

  Transform* transform_camera_1_;
  Camera* camera_1_;
  Transform* transform_camera_2_;
  Camera* camera_2_;
  vec2_ushort last_frame_mouse_position_;  // 上一帧的鼠标位置
};
