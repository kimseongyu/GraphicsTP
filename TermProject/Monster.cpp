#include "Monster.hpp"

// 생성자
Monster::Monster(int spawnX, int spawnY) {
  this->spawnX = spawnX;
  this->spawnY = spawnY;
  posX = spawnX;
  posY = spawnY;
  name = "monster";
  fullHP = 10;
  hp = 10;
  dmg = 2;
  gold = 100;
  genTime = 5000;
}

// 소멸자
Monster::~Monster() {}

// 초기화
void Monster::Init() {}

// 재설정
void Monster::Reset() {
  posX = spawnX;
  posY = spawnY;
  hp = fullHP;
}

// 갱신
void Monster::Update() { birth(); }

// 부활
void Monster::birth() {
  if (state != 0 || spawnTime > timer->getCrntTime()) return;
  Reset();
  setState(1);
}

// 죽음
void Monster::death() {
  long long crntTime = timer->getCrntTime();
  setSpawnTime(crntTime + this->getGenTime());
  setState(0);
}

// 강화
void Monster::upgrade() {
  dmg = dmg * 2;
  fullHP = fullHP *2;
  hp = fullHP *2;
  gold = gold + 50;
}

// getter, setter
int Monster::getSpawnX() { return spawnX; }

int Monster::getSpawnY() { return spawnY; }

long long Monster::getSkillCool() { return skillCool; }

long long Monster::getSkillTiming() { return skillTiming; }

long long Monster::getMoveCool() { return moveCool; }

void Monster::setSpawnX(int spawnX) { this->spawnX = spawnX; }

void Monster::setSpawnY(int spawnY) { this->spawnY = spawnY; }

void Monster::setSkillCool(long long skillCool) { this->skillCool = skillCool; }

void Monster::setSkillTiming(long long skillTiming) {
  this->skillTiming = skillTiming;
}

void Monster::setMoveCool(long long moveCool) { this->moveCool = moveCool; }