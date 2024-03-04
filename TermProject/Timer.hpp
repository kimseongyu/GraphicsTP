#pragma once

#include <chrono>
#include "Singleton.hpp"

using namespace std::chrono;

#define timer Timer::Get()

class Timer : public Singleton<Timer> {
 public:
  Timer();
  ~Timer();

  void Update();

  int DiffCrnt(long long milli);

  long long getCrntTime();

  void setCrntTime(long long crntTime);

 private:
  // 현재시간
  long long crntTime;
};