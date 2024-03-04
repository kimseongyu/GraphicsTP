#pragma once

#include "Equipment.hpp"
#include "Singleton.hpp"
#include "Timer.hpp"
#include "Unit.hpp"

#define player Player::Get()

class Player : public Singleton<Player>, public Unit {
 public:
  Player();
  ~Player();

  void Init();
  void Reset();
  void Update();

  void birth();
  void death();
  void takeDMG(int dmg);
  void Invincibility();

  void drink();
  void buyWeapon();
  void buyArmor();

  int getStage();
  long long getBumpCool();
  long long getSkillCool(int idx);
  Equipment* getWeapon();
  Equipment* getArmor();

  void setStage(int stage);
  void setBumpCool(long long bumpCool);
  void setSkillCool(int idx, long long t);

 private:
  // player�� ���� ��ġ�� �ܰ�
  int stage;
  // player�� monster�� ���浹������ �ð�
  long long bumpCool = 0;
  // player�� ��ų ����ð�
  long long skillCool[4] = {0};

  // ���ݷ��� �÷��ִ� weapon
  Equipment* weapon;
  // ü���� �÷��ִ� armor
  Equipment* armor;
};