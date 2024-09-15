#pragma once
#include <unordered_map>

class RenderDevice {
 public:
  enum class RenderState { None = 0, STENCIL_TEST };

 public:
  virtual void Enable(RenderState render_state);

  virtual void Disable(RenderState render_state);

 protected:
  std::unordered_map<RenderState, bool> render_state_map_;

 public:
  static void Init(RenderDevice* instance);

  static RenderDevice* instance() { return instance_; };

 private:
  static RenderDevice* instance_;
};
