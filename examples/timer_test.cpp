/**
 * @file timer_test.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-11-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "timer.h"

#include <unistd.h>
#include <iomanip>

int main() {
  Timer timer([]() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm* ptm = std::localtime(&tt);
    std::cout << "[" << std::put_time(ptm, "%c") << "] timer callback!!!" << std::endl;
  });

  //   timer.StartOnce(Timer::Clock::duration(std::chrono::seconds(10)));
  //   timer.StartPeriodicDelayed(Timer::Clock::duration(std::chrono::seconds(10)));
  timer.StartPeriodicImmediate(Timer::Clock::duration(std::chrono::seconds(10)));
  while (1) {
    sleep(100);
  }
  return 0;
}