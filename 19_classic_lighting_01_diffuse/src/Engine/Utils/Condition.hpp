#pragma once
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <functional>

class Condition {
public:
  Condition() {}
  bool Wait(const std::function<bool()>& predicate,
            const std::chrono::microseconds& timeout) {
    std::unique_lock<std::mutex> lock(m_cv_);
    return cv_.wait_for(lock, timeout, predicate);
  }
  void Signal(const std::function<void()>& fucntion) { 
    std::unique_lock<std::mutex> lock(m_cv_);
    fucntion();
    cv_.notify_all(); }

private:
  std::mutex m_cv_;
  std::condition_variable cv_;
};