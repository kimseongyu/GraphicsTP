#include "Timer.hpp"

// 생성자
Timer::Timer() {}

// 소멸자
Timer::~Timer() {}

// 현재 시간을 갱신
void Timer::Update() { 
  auto time = system_clock::now().time_since_epoch();
  this->crntTime = duration_cast<milliseconds>(time).count();
}

// 인자와 현재 시간과의 차이를 반환, 0보다 작으면 0으로 반환
int Timer::DiffCrnt(long long milli) { 
  milliseconds millisecondsDuration(crntTime - milli);
  int time = -duration_cast<seconds>(millisecondsDuration).count();
  return time > 0 ? time : 0;
}

// getter setter
long long Timer::getCrntTime() { return crntTime; }

void Timer::setCrntTime(long long crntTime) { this->crntTime = crntTime; }