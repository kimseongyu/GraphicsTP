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
  // player가 현재 위치한 단계
  int stage;
  // player가 monster와 재충돌까지의 시간
  long long bumpCool = 0;
  // player의 스킬 재사용시간
  long long skillCool[4] = {0};

  // 공격력을 올려주는 weapon
  Equipment* weapon;
  // 체력을 올려주는 armor
  Equipment* armor;
};