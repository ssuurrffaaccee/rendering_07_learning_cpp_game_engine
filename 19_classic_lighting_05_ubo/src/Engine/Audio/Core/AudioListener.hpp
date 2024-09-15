#pragma once
#include "Engine/Audio/Core/AudioClip.hpp"
#include "Engine/Component/Component.hpp"

class AudioListener : public Component {
 public:
  AudioListener();

  virtual void Awake();
  virtual void Update();

 private:
  unsigned int listener_id_ = 0;
  static unsigned int listener_num_;  // 已经创建的listener
  RTTR_ENABLE(Component);
};
