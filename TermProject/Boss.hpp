#pragma once

#include "Singleton.hpp"
#include "Unit.hpp"

#define boss Boss::Get()

class Boss : public Singleton<Boss>, public Unit {
 public:
  Boss();
  ~Boss();

  void Init();
  void Reset();
  void Update();

  void birth();
  void death();

  int getTargetX(int idx);
  int getTargetY(int idx);
  long long getSkillCool(int idx);
  long long getSkillTiming(int idx);
  long long getSkillTerm();
  long long getMoveCool();

  void setTargetX(int idx, int targetX);
  void setTargetY(int idx, int targetY);
  void setSkillCool(int idx, long long skillCool);
  void setSkillTiming(int idx, long long skillTiming);
  void setSkillTerm(long long skillTerm);
  void setMoveCool(long long moveCool);

 private:
  // 공격한 target의 위치
  int targetX[4] = {0};
  int targetY[4] = {0};
  // 스킬 전조 + 스킬 사용 후 대기 시간 포함
  long long skillCool[4] = {0};
  // 스킬 전조 후 데미지 나가는 시간
  long long skillTiming[4] = {0};
  // 스킬 사이의 간격
  long long skillTerm;
  // boss의 이동속도
  long long moveCool;
};