#include "Boss.hpp"

// ������
Boss::Boss() {}

// �Ҹ���
Boss::~Boss() {}

// �ʱ�ȭ
void Boss::Init() {
  posX = 10;
  posY = 0;
  name = "Boss";
  fullHP = 10000;
  hp = 10000;
  dmg = 32;
  state = 2;
}

// �缳��
void Boss::Reset() {}

// ����
void Boss::Update() { death(); }

// ��Ȱ
void Boss::birth() {}

// ����
void Boss::death() {
  if (hp > 0) return;
  setState(0);
}

// getter, setter
int Boss::getTargetX(int idx) { return targetX[idx]; }

int Boss::getTargetY(int idx) { return targetY[idx]; }

long long Boss::getSkillCool(int idx) { return skillCool[idx]; }

long long Boss::getSkillTiming(int idx) { return skillTiming[idx]; }

long long Boss::getSkillTerm() { return skillTerm; }

long long Boss::getMoveCool() { return moveCool; }

void Boss::setTargetX(int idx, int targetX) { this->targetX[idx] = targetX; }

void Boss::setTargetY(int idx, int targetY) { this->targetY[idx] = targetY; }

void Boss::setSkillCool(int idx, long long skillCool) {
  this->skillCool[idx] = skillCool;
}

void Boss::setSkillTiming(int idx, long long skillTiming) {
  this->skillTiming[idx] = skillTiming;
}

void Boss::setSkillTerm(long long skillTerm) { this->skillTerm = skillTerm; }

void Boss::setMoveCool(long long moveCool) { this->moveCool = moveCool; }
