/**
 * @file timer.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-11-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef COMMON_LIBRARY_TIMER_H
#define COMMON_LIBRARY_TIMER_H

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

namespace common {

class Timer {
 public:
  typedef std::chrono::steady_clock Clock;
  using TimerHandler = std::function<void(void)>;
  explicit Timer(TimerHandler handler);
  virtual ~Timer();
  void StartOnce(const Clock::duration timeout);
  void StartPeriodicImmediate(const Clock::duration timeout);
  void StartPeriodicDelayed(const Clock::duration timeout);
  inline bool IsRunning() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return running_;
  }
  inline bool IsPeriodic() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return kPeriodic == mode_;
  }
  inline void Stop() {
    std::lock_guard<std::mutex> lock(mutex_);
    running_ = false;
  }
  inline Clock::time_point GetNextExpiryPoint() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return next_expiry_point_;
  }

  inline Clock::duration GetTimeRemanning() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return next_expiry_point_ - Clock::now();
  }

 protected:
  void Run();

  enum Mode {
    kOneshot,
    kPeriodic,
  };
  TimerHandler timercb_func_;

  Mode mode_;

  std::atomic_bool exit_requested_;

  std::atomic<bool> running_;

  Clock::duration period_;

  Clock::time_point next_expiry_point_;

  mutable std::mutex mutex_;

  std::condition_variable cond_var_;

  std::thread thread_;
};
}  // namespace common

#endif