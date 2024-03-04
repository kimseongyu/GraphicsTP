#include "Game.hpp"

// ������
Game::Game() {}

// �Ҹ���
Game::~Game() {}

// �ʱ�ȭ
void Game::Init() {
  player->Init();
  // Monster �ʱ�ȭ
  MonsterList.push_back(new Monster(5, 9));
  MonsterList.push_back(new Monster(-4, 8));
  MonsterList.push_back(new Monster(-2, -10));
  MonsterList.push_back(new Monster(-9, -1));
  MonsterList.push_back(new Monster(8, -4));
  // boss �ʱ�ȭ
  boss->Init();
  // game ���࿩�� ����
  gameRun = true;
}

// game ����
// game ���� ���ΰ� true�� �� ���� ���������� ��ü���� ���¸� ����
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

// game ����
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