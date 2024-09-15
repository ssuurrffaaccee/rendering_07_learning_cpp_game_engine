#include <chrono>
#include <iostream>
#include <string>
class TimeRecord {
public:
  using ClockType = decltype(std::chrono::steady_clock::now());
  TimeRecord(const std::string &name) : name_{name} {
    last_ = std::chrono::steady_clock::now();
  }
  ~TimeRecord() {
    auto now = std::chrono::steady_clock::now();
    long duration =
        (long)std::chrono::duration_cast<std::chrono::milliseconds>(now - last_)
            .count();
    std::cout << name_ << " time: " << (float)duration << " ms\n";
  }
  std::string name_;
  ClockType last_;
};