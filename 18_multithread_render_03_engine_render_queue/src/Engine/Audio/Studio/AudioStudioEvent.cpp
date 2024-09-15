#include "Engine/Audio/Studio/AudioStudioEvent.hpp"
#include "Engine/Component/GameObject.hpp"
#include "Engine/Component/Transform.hpp"
#include "Engine/Utils/Debug.hpp"

AudioStudioEvent::AudioStudioEvent() {}
AudioStudioEvent::~AudioStudioEvent(){}


FMOD_RESULT AudioStudioEvent::SetParameterByName(const char *name, float value, bool ignore_seek_speed) {
    return FMOD_Studio_EventInstance_SetParameterByName(event_instance_,name,value,ignore_seek_speed);
}

FMOD_RESULT AudioStudioEvent::Set3DAttribute(float x,float y,float z){
    FMOD_3D_ATTRIBUTES attributes = { { x,y,z } };
    return FMOD_Studio_EventInstance_Set3DAttributes(event_instance_,&attributes);
}

void AudioStudioEvent::Start() {
    if(event_instance_== nullptr){
        DEBUG_LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result=FMOD_Studio_EventInstance_Start(event_instance_);
    if(result!=FMOD_OK){
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_Start result:{}",int(result));
        return;
    }
}

void AudioStudioEvent::Pause() {
    if(event_instance_== nullptr){
        DEBUG_LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result=FMOD_Studio_EventInstance_SetPaused(event_instance_,true);
    if(result!=FMOD_OK){
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_SetPaused result:{}",int(result));
        return;
    }
}

void AudioStudioEvent::Stop() {
    if(event_instance_== nullptr){
        DEBUG_LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result=FMOD_Studio_EventInstance_Stop(event_instance_,FMOD_STUDIO_STOP_MODE::FMOD_STUDIO_STOP_IMMEDIATE);
    if(result!=FMOD_OK){
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_Stop result:{}",int(result));
        return;
    }
}
