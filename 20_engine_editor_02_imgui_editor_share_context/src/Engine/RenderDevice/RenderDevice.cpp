#include "Engine/RenderDevice/RenderDevice.hpp"

RenderDevice* RenderDevice::instance_;

void RenderDevice::Enable(RenderDevice::RenderState render_state) {
  render_state_map_[render_state] = true;
}

void RenderDevice::Disable(RenderDevice::RenderState render_state) {
  render_state_map_[render_state] = false;
}

void RenderDevice::Init(RenderDevice* instance) { instance_ = instance; }