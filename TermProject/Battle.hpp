#pragma once

#include <string>
#include <random>
#include "Singleton.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Boss.hpp"
#include "Game.hpp"
#include "Timer.hpp"

#define battle Battle::Get()

class Battle: public Singleton<Battle> {
 public:
  Battle();
  ~Battle();

  void monsterUpdate(Monster* monster);

  void bossUpdate();

  void playerAtk(int scope[][5], float coef);
  bool playerSkill(int skillNum);

  void monsterAtk(int scope[][5], Monster* monster);
  void monsterSkill(Monster* monster);

  void bossSkill0();
  void bossSkill1();
  void bossSkill2();
  void bossSkill3();
  void bossSkill();

  void bump(Monster* monster);
  void bossBump();

  void nextStage();

  int distMonster(int mX, int mY);

  void monsterMove(Monster* monster);
  void bossMove();

 private:
  int dx[4] = {1, 0, -1, 0};
  int dy[4] = {0, 1, 0, -1};
};