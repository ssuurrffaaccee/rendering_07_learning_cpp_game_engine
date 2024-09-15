#pragma once

#include "fmod/api/core/inc/fmod.h"

class Audio {
 public:
  /// 初始化fmod
  static void Init();

  /// 刷帧
  /// \return
  static void Update();
};
