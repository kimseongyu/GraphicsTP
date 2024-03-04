#include "Game.hpp"

// 생성자
Game::Game() {}

// 소멸자
Game::~Game() {}

// 초기화
void Game::Init() {
  player->Init();
  // Monster 초기화
  MonsterList.push_back(new Monster(5, 9));
  MonsterList.push_back(new Monster(-4, 8));
  MonsterList.push_back(new Monster(-2, -10));
  MonsterList.push_back(new Monster(-9, -1));
  MonsterList.push_back(new Monster(8, -4));
  // boss 초기화
  boss->Init();
  // game 실행여부 설정
  gameRun = true;
}

// game 실행
// game 실행 여부가 true일 때 동안 지속적으로 객체들의 상태를 갱신
void Game::Run() {
  while (gameRun == true) {
    timer->Update();
    player->Update();
    list<Monster*>::iterator It;
    for (It = MonsterList.begin(); It != MonsterList.end(); It++) {
      (*It)->Update();
      battle->monsterUpdate(*It);
    }
    if (boss->getState() == 1) {
      boss->Update();
      battle->bossUpdate();
    }
  }
}

// game 종료
void Game::Quit() {
  player->Del();
  boss->Del();
  list<Monster*>::iterator It;
  for (It = MonsterList.begin(); It != MonsterList.end(); It++) delete (*It);
  exit(0);
}

// getter, setter
list<Monster*>* Game::getMonsterList() { return &MonsterList; }

void Game::setMonsterList(list<Monster*>* mList) { this->MonsterList = *mList; }