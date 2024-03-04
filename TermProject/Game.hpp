#pragma once

#include <list>
#include <thread>

#include "Battle.hpp"
#include "Boss.hpp"
#include "Draw.hpp"
#include "Monster.hpp"
#include "Player.hpp"
#include "Singleton.hpp"
#include "Timer.hpp"

using namespace std;

#define game Game::Get()

class Game : public Singleton<Game> {
 public:
  Game();
  ~Game();

  void Init();
  void Run();
  void Quit();

  list<Monster*>* getMonsterList();
  void setMonsterList(list<Monster*>* mList);

 private:
  // 게임 진행여부
  bool gameRun;
  // game에 소환된 monster list
  list<Monster*> MonsterList;
};