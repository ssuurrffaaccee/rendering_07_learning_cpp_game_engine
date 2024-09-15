#include <chrono>
#include <iostream>
#include <string>
class TimeRecorder {
public:
  using ClockType = decltype(std::chrono::steady_clock::now());
  TimeRecorder(const std::string &name) : name_{name} {
    last_ = std::chrono::steady_clock::now();
  }
  ~TimeRecorder() {
    auto now = std::chrono::steady_clock::now();
    long duration =
        (long)std::chrono::duration_cast<std::chrono::milliseconds>(now - last_)
            .count();
    std::cout << name_ << " time: " << (float)duration << " ms\n";
  }
  std::string name_;
  ClockType last_;
};