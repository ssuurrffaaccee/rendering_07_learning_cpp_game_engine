#include "Engine/RenderDevice/RenderTaskConsumer.hpp"
#include "Engine/RenderDevice/RenderTaskConsumerBase.hpp"

RenderTaskConsumerBase* RenderTaskConsumer::instance_= nullptr;


void RenderTaskConsumer::Init(RenderTaskConsumerBase* instance) {
    instance_ = instance;
    instance_->Init();
}

RenderTaskConsumerBase* RenderTaskConsumer::Instance() {
    return instance_;
}

void RenderTaskConsumer::Exit() {
    instance_->Exit();
}