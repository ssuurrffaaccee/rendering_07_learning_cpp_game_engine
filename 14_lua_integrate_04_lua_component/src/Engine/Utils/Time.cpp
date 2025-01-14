#include "Engine/Utils/Time.hpp"

std::chrono::system_clock::time_point Time::startup_time_;
float Time::delta_time_ = 0;
float Time::last_frame_time_ = 0;

Time::Time() {}

Time::~Time() {}

void Time::Init() { startup_time_ = std::chrono::system_clock::now(); }

void Time::Update() {
  if (last_frame_time_ > 0) {
    delta_time_ = TimeSinceStartup() - last_frame_time_;
  }
  last_frame_time_ = TimeSinceStartup();
}

float Time::TimeSinceStartup() {
  std::chrono::time_point now = std::chrono::system_clock::now();
  uint64_t ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - startup_time_)
          .count();
  return ms / 1000.0f;
}