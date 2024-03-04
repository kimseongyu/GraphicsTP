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
  // monster�� spawn�Ǵ� ��ġ
  int spawnX;
  int spawnY;
  // ��ų ���� + ��ų ��� �� ��� �ð� ����
  long long skillCool;
  // ��ų ���� �� ������ ������ �ð�
  long long skillTiming;
  // ���� �̵� ��Ÿ��
  long long moveCool;
};