#pragma once
#include "Engine/RenderDevice/RenderDevice.hpp"
class RenderDeviceOpenGL : public RenderDevice {
 public:
  void Enable(RenderState render_state) override;

  void Disable(RenderState render_state) override;
};
