#include "Unit.hpp"

// 생성자
Unit::Unit() {
  state = 1;
  spawnTime = 0;
}

// 소멸자
Unit::~Unit() {}

// Unit의 변수에 대한 getter setter
int Unit::getPosX() { return posX; }

int Unit::getPosY() { return posY; }

const char* Unit::getName() { return name; }

int Unit::getHP() { return hp; }

int Unit::getFullHP() { return fullHP; }

int Unit::getDMG() { return dmg; }

int Unit::getGold() { return gold; }

int Unit::getState() { return state; }

long long Unit::getSpawnTime() { return spawnTime; }

long long Unit::getGenTime() { return genTime; }

void Unit::setPosX(int posX) { this->posX = posX; }

void Unit::setPosY(int posY) { this->posY = posY; }

void Unit::setName(const char* name) { this->name = name; }

void Unit::setHP(int hp) { this->hp = hp; }

void Unit::setFullHP(int fullHP) { this->fullHP = fullHP; }

void Unit::setDMG(int dmg) { this->dmg = dmg; }

void Unit::setGold(int gold) { this->gold = gold; }

void Unit::setState(int state) { this->state = state; }

void Unit::setSpawnTime(long long spawnTime) { this->spawnTime = spawnTime; }

void Unit::setGenTime(long long genTime) { this->genTime = genTime; }