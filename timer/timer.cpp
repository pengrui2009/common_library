/**
 * @file timer.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-11-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <timer.h>

Timer::Timer(TimerHandler handler)
    : timercb_func_(handler), mode_(Timer::Mode::kOneshot), exit_requested_(false), running_(false) {
  thread_ = std::thread(&Timer::Run, this);
}

Timer::~Timer() {
  exit_requested_ = true;
  Stop();
  cond_var_.notify_all();
  thread_.join();
}

void Timer::StartOnce(const Clock::duration timeout) {
  std::unique_lock<std::mutex> lock(mutex_);
  mode_ = kOneshot;
  next_expiry_point_ = Clock::now() + timeout;
  running_.store(true, std::memory_order_release);
  cond_var_.notify_all();
  return;
}

void Timer::StartPeriodicImmediate(const Clock::duration period) {
  std::unique_lock<std::mutex> lock(mutex_);
  mode_ = kPeriodic;
  next_expiry_point_ = Clock::now();
  period_ = period;
  running_.store(true, std::memory_order_release);
  cond_var_.notify_all();
  return;
}
void Timer::StartPeriodicDelayed(const Clock::duration period) {
  std::unique_lock<std::mutex> lock(mutex_);
  mode_ = kPeriodic;
  next_expiry_point_ = Clock::now() + period;
  period_ = period;
  running_.store(true, std::memory_order_release);
  cond_var_.notify_all();
  return;
}

void Timer::Run() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (!exit_requested_) {
    // Block until timer expires or timer is started again
    if (running_.load()) {
      cond_var_.wait_until(lock, next_expiry_point_);
    } else {
      cond_var_.wait(lock);
    }
    if (running_.load()) {
      if (next_expiry_point_ <= Clock::now()) {
        // Unlock the mutex during a potentially long-running operation
        lock.unlock();
        timercb_func_();
        lock.lock();
        // Determine if we have to set the timer again
        if (kOneshot == mode_) {
          running_ = false;
        } else {
          next_expiry_point_ += period_;
        }
      }
    }
  }
  return;
}