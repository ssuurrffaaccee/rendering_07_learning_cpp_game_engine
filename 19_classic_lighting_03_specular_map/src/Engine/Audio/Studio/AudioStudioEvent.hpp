#pragma once
#include "fmod/api/core/inc/fmod.h"
#include "fmod/api/studio/inc/fmod_studio.h"

class AudioStudioEvent {
public:
    AudioStudioEvent();
    ~AudioStudioEvent();

    FMOD_STUDIO_EVENTINSTANCE* event_instance(){return event_instance_;}
    void set_event_instance(FMOD_STUDIO_EVENTINSTANCE* event_instance){event_instance_=event_instance;}

    /// 设置Event参数
    /// \param name
    /// \param value
    /// \param ignore_seek_speed
    /// \return
    FMOD_RESULT SetParameterByName(const char *name, float value, bool ignore_seek_speed = false);

    /// 设置Event 3D属性
    /// \param x
    /// \param y
    /// \param z
    /// \return
    FMOD_RESULT Set3DAttribute(float x,float y,float z);

    /// 播放Event实例
    void Start();

    void Stop();

    /// 暂停
    void Pause();
private:
    FMOD_STUDIO_EVENTINSTANCE* event_instance_;
};
