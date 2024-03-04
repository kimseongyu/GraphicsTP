#include "Timer.hpp"

// ������
Timer::Timer() {}

// �Ҹ���
Timer::~Timer() {}

// ���� �ð��� ����
void Timer::Update() { 
  auto time = system_clock::now().time_since_epoch();
  this->crntTime = duration_cast<milliseconds>(time).count();
}

// ���ڿ� ���� �ð����� ���̸� ��ȯ, 0���� ������ 0���� ��ȯ
int Timer::DiffCrnt(long long milli) { 
  milliseconds millisecondsDuration(crntTime - milli);
  int time = -duration_cast<seconds>(millisecondsDuration).count();
  return time > 0 ? time : 0;
}

// getter setter
long long Timer::getCrntTime() { return crntTime; }

void Timer::setCrntTime(long long crntTime) { this->crntTime = crntTime; }