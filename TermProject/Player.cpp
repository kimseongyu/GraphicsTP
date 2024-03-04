#include "Player.hpp"

// ������
Player::Player() {
};

// �Ҹ���
Player::~Player() {}

// �ʱ�ȭ
void Player::Init() {
  posX = 0;
  posY = 0;
  name = "player";
  hp = 20;
  fullHP = 20;
  dmg = 2;
  gold = 0;
  genTime = 5000;

  stage = 1;

  weapon = new Equipment(1000, 2);
  armor = new Equipment(500, 20);
}

// �缳��
void Player::Reset() {
  posX = 0;
  posY = 0;
  hp = fullHP;
  gold = gold / 2;
};

// ���� update
void Player::Update() {
  death();
  birth();
  Invincibility();
}

// ��Ȱ
void Player::birth() {
  if (state != 0 || spawnTime > timer->getCrntTime()) return;
  Reset();
  setState(1);
}

// ����
void Player::death() {
  long long crntTime = timer->getCrntTime();
  if (state == 0 || hp > 0) return;
  setSpawnTime(crntTime + this->getGenTime());
  setState(0);
}

// ������ �ޱ�
void Player::takeDMG(int dmg) {
  if (state == 2) return;
  int hp = this->hp - dmg;
  setHP(hp >= 0 ? hp : 0);
}

// ���� ���� ���� �� ����
void Player::Invincibility() {
  long long crntTime = timer->getCrntTime();
  if (player->getState() == 2 && player->getSkillCool(1) <= crntTime) {
    player->setState(1);
    player->setSkillCool(1, crntTime + 6000);
  }
}

// ���� ����
void Player::drink() {
  if (gold < 1000 || hp == fullHP) return;
  setGold(gold - 1000);
  int recoveredHP = hp + 25;
  if (recoveredHP > fullHP) {
    setHP(fullHP);
  } else {
    setHP(recoveredHP);
  }
}

// ���� ����
void Player::buyWeapon() {
  int cost = weapon->getCost();
  int ability = weapon->getAbility();
  if (gold < cost) return;
  setDMG(dmg + ability);
  setGold(gold - cost);
  weapon->setLevel(weapon->getLevel() + 1);
  weapon->setCost(weapon->getCost() + 1000);
  weapon->setAbility(weapon->getAbility() * 2);
}

// �� ����
void Player::buyArmor() {
  int cost = armor->getCost();
  int ability = armor->getAbility();
  if (gold < cost) return;
  setHP(getHP() + ability);
  setGold(gold - cost);
  setFullHP(getFullHP() + ability);
  armor->setLevel(armor->getLevel() + 1);
  armor->setCost(armor->getCost() + 500);
}

// getter, setter
int Player::getStage() { return stage; }

long long Player::getBumpCool() { return bumpCool; }

long long Player::getSkillCool(int idx) { return skillCool[idx]; }

Equipment* Player::getWeapon() { return weapon; }

Equipment* Player::getArmor() { return armor; }

void Player::setStage(int stage) { this->stage = stage; }

void Player::setBumpCool(long long bumpCool) { this->bumpCool = bumpCool; }

void Player::setSkillCool(int idx, long long t) { this->skillCool[idx] = t; }