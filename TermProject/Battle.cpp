#include "Battle.hpp"

// ������
Battle::Battle() {}

// �Ҹ���
Battle::~Battle() {}

// monster�� ���� ���� ����
void Battle::monsterUpdate(Monster* monster) {
  if (monster->getState() == 0 || player->getState() == 0) return;
  monsterMove(monster);
  if (distMonster(monster->getPosX(), monster->getPosY()) > 5) return;
  bump(monster);
  monsterSkill(monster);
}

// boss�� ���� ���� ����
void Battle::bossUpdate() {
  if (player->getState() == 0) return;
  bossMove();
  bossBump();
  bossSkill();
}

// ���ݹ����� ����� �Է¹޾� player�� ���� ����
void Battle::playerAtk(int scope[][5], float coef) {
  int pX = player->getPosX() - 2;
  int pY = player->getPosY() - 2;

  // ����� ���� ���� ������ ����
  int dmg = coef * player->getDMG();

  // monster Ÿ��, ���� ���� monster�� �����ϴ��� Ȯ��
  list<Monster*>::iterator It;
  list<Monster*> monsterList = *(game->getMonsterList());
  for (It = monsterList.begin(); It != monsterList.end(); It++) {
    int mX = (*It)->getPosX();
    int mY = (*It)->getPosY();
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (scope[i][j] == 0) continue;
        if (pX + i == mX && pY + j == mY) {
          (*It)->setHP((*It)->getHP() - dmg);
        }
      }
    }
    if ((*It)->getState() == 0 || (*It)->getHP() > 0) continue;
    (*It)->death();
    player->setGold(player->getGold() + (*It)->getGold());
  }

  // boss Ÿ��, ���� ���� monster�� �����ϴ��� Ȯ��
  int bX = boss->getPosX();
  int bY = boss->getPosY();
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (scope[i][j] == 0) continue;
      if ((pX + i >= bX - 1 && pX + i <= bX + 1) &&
          (pY + j >= bY - 1 && pY + j <= bY + 1)) {
        int bHP = boss->getHP() - dmg;
        boss->setHP(bHP > 0 ? bHP : 0);
        return;
      }
    }
  }
}

// key �Է¿� ���� skillNum�� �Ѱ� ����
// skill ��ȣ�� ���� ���� ������ ����� ���Ͽ� �����Լ��� ����
// ���� ���� �� cooltime �ʱ�ȭ
bool Battle::playerSkill(int skillNum) {
  long long crntTime = timer->getCrntTime();
  if (player->getSkillCool(skillNum) > crntTime) return false;
  switch (skillNum) {
    case 0: {
      int scope[5][5] = {{0, 0, 0, 0, 0},
                         {0, 1, 1, 1, 0},
                         {0, 1, 1, 1, 0},
                         {0, 1, 1, 1, 0},
                         {0, 0, 0, 0, 0}};
      playerAtk(scope, 1);
      player->setSkillCool(0, crntTime + 100);
    } break;
    case 1: {
      player->setState(2);
      player->setSkillCool(1, crntTime + 2000);
    } break;
    case 2: {
      int scope[5][5] = {{1, 1, 1, 1, 1},
                         {1, 0, 1, 0, 1},
                         {1, 1, 1, 1, 1},
                         {1, 0, 1, 0, 1},
                         {1, 1, 1, 1, 1}};
      playerAtk(scope, 3);
      player->setSkillCool(2, crntTime + 3000);
    } break;
    case 3: {
      int scope[5][5] = {{0, 0, 0, 0, 0},
                         {0, 0, 1, 0, 0},
                         {0, 1, 1, 1, 0},
                         {0, 0, 1, 0, 0},
                         {0, 0, 0, 0, 0}};
      playerAtk(scope, 10);
      player->setSkillCool(3, crntTime + 10000);
    } break;
    default:
      break;
  }
  return true;
}

// ���ݹ����� �޾Ƽ� ���� ������ player�� �����ϸ� ����
// monster�� ���ݷ¸�ŭ player���� ���ظ� ��
// 1ȸ Ÿ�� �� ����
void Battle::monsterAtk(int scope[][5], Monster* monster) {
  int mX = monster->getPosX() - 2;
  int mY = monster->getPosY() - 2;
  int pX = player->getPosX();
  int pY = player->getPosY();
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (scope[i][j] == 0) continue;
      if (mX + i == pX && mY + j == pY) {
        player->takeDMG(monster->getDMG());
        monster->setSkillTiming(monster->getSkillCool());
        return;
      }
    }
  }
}

// player�� ��ġ�� stage ������ ���� ���� ������ ����
// ������ monster�� ���ݹ����� monster�� �����Լ��� ����
void Battle::monsterSkill(Monster* monster) {
  long long crntTime = timer->getCrntTime();
  long long skillCool = monster->getSkillCool();
  long long skillTiming = monster->getSkillTiming();

  // crnt�� cool���� ũ�� skill ����, Time�� Cool ����
  if (skillCool <= crntTime) {
    switch (player->getStage()) {
      case 1: {
        monster->setSkillCool(crntTime + 3000);
        monster->setSkillTiming(crntTime + 1000);
      } break;
      case 2: {
        monster->setSkillCool(crntTime + 3000);
        monster->setSkillTiming(crntTime + 1000);
      } break;
      case 3: {
        monster->setSkillCool(crntTime + 3000);
        monster->setSkillTiming(crntTime + 1000);
      } break;
      case 4: {
        monster->setSkillCool(crntTime + 3000);
        monster->setSkillTiming(crntTime + 1000);
      } break;
      case 5: {
        monster->setSkillCool(crntTime + 3000);
        monster->setSkillTiming(crntTime + 1000);
      } break;
      default:
        break;
    }
  }
  // crnt�� cool���� �۰� timing���� ũ�� skill ������ ��
  else if (skillTiming <= crntTime) {
    switch (player->getStage()) {
      case 1: {
        int scope[][5] = {{0, 0, 0, 0, 0},
                          {0, 0, 1, 0, 0},
                          {0, 1, 1, 1, 0},
                          {0, 0, 1, 0, 0},
                          {0, 0, 0, 0, 0}};
        monsterAtk(scope, monster);
      } break;
      case 2: {
        int scope[][5] = {{0, 0, 0, 0, 0},
                          {0, 1, 1, 1, 0},
                          {0, 1, 1, 1, 0},
                          {0, 1, 1, 1, 0},
                          {0, 0, 0, 0, 0}};
        monsterAtk(scope, monster);
      } break;
      case 3: {
        int scope[][5] = {{0, 1, 0, 1, 0},
                          {1, 1, 1, 1, 1},
                          {0, 1, 1, 1, 0},
                          {1, 1, 1, 1, 1},
                          {0, 1, 0, 1, 0}};
        monsterAtk(scope, monster);
      } break;
      case 4: {
        int scope[][5] = {{1, 0, 1, 0, 1},
                          {0, 1, 1, 1, 0},
                          {1, 1, 1, 1, 1},
                          {0, 1, 1, 1, 0},
                          {1, 0, 1, 0, 1}};
        monsterAtk(scope, monster);
      } break;
      case 5: {
        int scope[][5] = {{1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1}};
        monsterAtk(scope, monster);
      } break;
      default:
        break;
    }
    monster->setSkillTiming(skillCool);
  }
  // crnt�� cool�� timing���� ũ�� skill ���� ���� ���
  // -> draw���� ����
}

// boss�� 0��° skill - ���� player ��ġ�� ���� ����
void Battle::bossSkill0() {
  int pX = player->getPosX();
  int pY = player->getPosY();
  int tX = boss->getTargetX(0) - 1;
  int tY = boss->getTargetY(0) - 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (pX == tX + i && pY == tY + j) {
        player->takeDMG(10);
      }
    }
  }
};

// boss�� 1��° skill - monster ����
void Battle::bossSkill1() {
  int pX = player->getPosX();
  int pY = player->getPosY();
  list<Monster*>::iterator It;
  list<Monster*> monsterList = *(game->getMonsterList());
  for (It = monsterList.begin(); It != monsterList.end(); It++) {
    if ((*It)->getState() == 0) continue;
    int mX = (*It)->getPosX() - 1;
    int mY = (*It)->getPosY() - 1;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (pX == mX + i && pY == mY + j) {
          player->takeDMG(30);
        }
      }
    }
    (*It)->death();
  }
};

// boss�� 2��° skill - boss �ֺ��� ����
void Battle::bossSkill2() {
  int pX = player->getPosX();
  int pY = player->getPosY();
  int bX = boss->getPosX() - 4;
  int bY = boss->getPosY() - 4;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (pX == bX + i && pY == bY + j) {
        player->takeDMG(30);
        return;
      }
    }
  }
};

// boss�� 3��° skill - map �߾Ӻκп� ������ ����
void Battle::bossSkill3() {
  int pX = player->getPosX();
  int pY = player->getPosY();
  for (int i = -10; i < 12; i++) {
    for (int j = -10; j < 12; j++) {
      if (pX == i && pY == j) {
        player->takeDMG(50);
      }
    }
  }
};

// ��ų�� �����ϰ� ������ ��ų�� ���
void Battle::bossSkill() {
  long long crntTime = timer->getCrntTime();
  // ������ ��ų ���
  for (int i = 0; i < 4; i++) {
    if (boss->getSkillCool(i) > crntTime &&
        boss->getSkillTiming(i) <= crntTime) {
      switch (i) {
        case 0:
          bossSkill0();
          break;
        case 1:
          bossSkill1();
          break;
        case 2:
          bossSkill2();
          break;
        case 3:
          bossSkill3();
          break;
        default:
          break;
      }
      boss->setSkillTiming(i, boss->getSkillCool(i));
    }
  }

  // ��ų ����
  // ������ ������ ��ų�� �ð����̰� �󸶳��� ������ �������� ���� 
  // random�ϰ� ���� ���ؼ� boss�� ����� skill�� ����
  // ���� ���ؼ� �˸��� �Լ��� ȣ��
  if (boss->getSkillTerm() > crntTime) return;
  random_device rd;
  mt19937 mersenne(rd());
  uniform_int_distribution<> die(0, 4);
  int rand = die(mersenne);
  boss->setSkillTerm(crntTime + 1000);
  switch (rand) {
    case 0: {
      if (boss->getSkillCool(0) <= crntTime) {
        boss->setTargetX(0, player->getPosX());
        boss->setTargetY(0, player->getPosY());
        boss->setSkillCool(0, crntTime + 2000);
        boss->setSkillTiming(0, crntTime + 1000);
      }
    } break;
    case 1: {
      if (boss->getSkillCool(1) <= crntTime) {
        boss->setSkillCool(1, crntTime + 10000);
        boss->setSkillTiming(1, crntTime + 2000);
      }
    } break;
    case 2: {
      if (distMonster(boss->getPosX(), boss->getPosY()) <= 5 &&
          boss->getSkillCool(2) <= crntTime) {
        boss->setSkillCool(2, crntTime + 2000);
        boss->setSkillTiming(2, crntTime + 1000);
      }
    } break;
    case 3: {
      if (boss->getSkillCool(3) <= crntTime) {
        boss->setSkillCool(3, crntTime + 10000);
        boss->setSkillTiming(3, crntTime + 3000);
      }
    } break;
    default:
      break;
  }
};

// monster�� player���� �浹�߻��� player�� �޴� ������ ����
void Battle::bump(Monster* monster) {
  long long bumpCool = timer->getCrntTime();
  if (player->getBumpCool() > bumpCool) return;

  int pX = player->getPosX();
  int pY = player->getPosY();
  int mX = monster->getPosX();
  int mY = monster->getPosY();

  if (pX != mX || pY != mY) return;
  player->takeDMG(player->getStage());
  player->setBumpCool(bumpCool + 1000);
}

// boss�� player���� �浹�߻��� player�� �޴� ������ ����
void Battle::bossBump() {
  long long bumpCool = timer->getCrntTime();
  if (player->getBumpCool() > bumpCool) return;

  int pX = player->getPosX();
  int pY = player->getPosY();
  int bX = boss->getPosX();
  int bY = boss->getPosY();

  if ((pX >= bX - 1 && pX <= bX + 1) && (pY >= bY - 1 && pY <= bY + 1)) {
    player->takeDMG(10);
    player->setBumpCool(bumpCool + 1000);
  }
}

// gŰ�� ���� ���� stage�� �Ѿ�� ���� ����
// monster�� ���� �ܰ�� upgrade��Ŵ
// boss stage ���� �� ������ ���¸� Ȱ�� ����(1)�� ����
void Battle::nextStage() {
  int stage = player->getStage();
  if (stage > 5) return;
  player->setStage(stage + 1);

  list<Monster*>::iterator It;
  list<Monster*> monsterList = *(game->getMonsterList());
  for (It = monsterList.begin(); It != monsterList.end(); It++) {
    (*It)->upgrade();
  }
  if (stage == 5) boss->setState(1);
}

// �־��� ��ǥ�� player���� �Ÿ��� ���Ͽ� ��ȯ
int Battle::distMonster(int mX, int mY) {
  int dist = 0;
  int pX = player->getPosX();
  int pY = player->getPosY();

  if (pX < mX)
    dist += mX - pX;
  else
    dist += pX - mX;

  if (pY < mY)
    dist += mY - pY;
  else
    dist += pY - mY;

  return dist;
}

// monster�� player�� ����� ��ġ�� �̵�
void Battle::monsterMove(Monster* monster) {
  if (monster->getMoveCool() > timer->getCrntTime()) return;
  int mX = monster->getPosX();
  int mY = monster->getPosY();
  int dist = distMonster(mX, mY);
  for (int i = 0; i < 4; i++) {
    int mdX = mX + dx[i];
    int mdY = mY + dy[i];
    if (distMonster(mdX, mdY) >= dist) continue;
    monster->setPosX(mdX);
    monster->setPosY(mdY);
    monster->setMoveCool(timer->getCrntTime() + 1000);
    return;
  }
}

// boss�� player�� ����� ��ġ�� �̵�
void Battle::bossMove() {
  if (boss->getMoveCool() > timer->getCrntTime()) return;
  int mX = boss->getPosX();
  int mY = boss->getPosY();
  int dist = distMonster(mX, mY);
  for (int i = 0; i < 4; i++) {
    int mdX = mX + dx[i];
    int mdY = mY + dy[i];
    if (distMonster(mdX, mdY) >= dist) continue;
    boss->setPosX(mdX);
    boss->setPosY(mdY);
    boss->setMoveCool(timer->getCrntTime() + 1000);
    return;
  }
}