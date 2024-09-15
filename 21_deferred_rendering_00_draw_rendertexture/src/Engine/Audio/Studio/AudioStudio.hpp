#pragma once
#include <iostream>
#include "fmod/api/core/inc/fmod.h"
#include "fmod/api/studio/inc/fmod_studio.h"
#include "Engine/Audio/Studio/AudioStudioEvent.hpp"

using namespace std;

class AudioStudio {
public:
    /// 初始化FMOD Studio
    /// \return
    static FMOD_RESULT Init();

    /// 刷帧
    /// \return
    static FMOD_RESULT Update();

    /// 加载 bank 文件
    /// \param file_name
    /// \return
    static FMOD_RESULT LoadBankFile(string file_name);

    /// 获取Event实例，如果没有就创建。
    /// \param event_path
    /// \return
    static AudioStudioEvent* CreateEventInstance(const char *event_path);

    /// 设置听者属性
    /// \param x
    /// \param y
    /// \param z
    static void SetListenerAttributes(float x,float y,float z);

private:
    static FMOD_STUDIO_SYSTEM* system_;
};
