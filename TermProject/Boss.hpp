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
  // ������ target�� ��ġ
  int targetX[4] = {0};
  int targetY[4] = {0};
  // ��ų ���� + ��ų ��� �� ��� �ð� ����
  long long skillCool[4] = {0};
  // ��ų ���� �� ������ ������ �ð�
  long long skillTiming[4] = {0};
  // ��ų ������ ����
  long long skillTerm;
  // boss�� �̵��ӵ�
  long long moveCool;
};