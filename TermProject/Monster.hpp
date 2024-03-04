#pragma once

#include "Timer.hpp"
#include "Unit.hpp"

class Monster : public Unit {
 public:
  Monster(int spawnX, int spawnY);
  ~Monster();

  void Init();
  void Reset();
  void Update();

  void birth();
  void death();
  void upgrade();

  int getSpawnX();
  int getSpawnY();
  long long getSkillCool();
  long long getSkillTiming();
  long long getMoveCool();

  void setSpawnX(int spawnX);
  void setSpawnY(int spawnY);
  void setSkillCool(long long skillCool);
  void setSkillTiming(long long skillTiming);
  void setMoveCool(long long moveCool);

 private:
  // monster가 spawn되는 위치
  int spawnX;
  int spawnY;
  // 스킬 전조 + 스킬 사용 후 대기 시간 포함
  long long skillCool;
  // 스킬 전조 후 데미지 나가는 시간
  long long skillTiming;
  // 몬스터 이동 쿨타임
  long long moveCool;
};