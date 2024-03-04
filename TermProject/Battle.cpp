#include "Battle.hpp"

// 생성자
Battle::Battle() {}

// 소멸자
Battle::~Battle() {}

// monster의 전투 상태 갱신
void Battle::monsterUpdate(Monster* monster) {
  if (monster->getState() == 0 || player->getState() == 0) return;
  monsterMove(monster);
  if (distMonster(monster->getPosX(), monster->getPosY()) > 5) return;
  bump(monster);
  monsterSkill(monster);
}

// boss의 전투 상태 갱신
void Battle::bossUpdate() {
  if (player->getState() == 0) return;
  bossMove();
  bossBump();
  bossSkill();
}

// 공격범위와 계수를 입력받아 player가 공격 수행
void Battle::playerAtk(int scope[][5], float coef) {
  int pX = player->getPosX() - 2;
  int pY = player->getPosY() - 2;

  // 계수를 통해 입힐 데미지 설정
  int dmg = coef * player->getDMG();

  // monster 타격, 범위 내에 monster가 존재하는지 확인
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

  // boss 타격, 범위 내에 monster가 존재하는지 확인
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

// key 입력에 따라 skillNum을 넘겨 받음
// skill 번호에 따라 공격 범위와 계수를 정하여 공격함수에 전달
// 공격 진행 후 cooltime 초기화
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

// 공격범위를 받아서 공격 범위에 player가 존재하면 공격
// monster의 공격력만큼 player에게 피해를 줌
// 1회 타격 후 종료
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

// player가 위치한 stage 정보에 따라 공격 범위를 정함
// 공격할 monster와 공격범위를 monster의 공격함수에 전달
void Battle::monsterSkill(Monster* monster) {
  long long crntTime = timer->getCrntTime();
  long long skillCool = monster->getSkillCool();
  long long skillTiming = monster->getSkillTiming();

  // crnt가 cool보다 크면 skill 시작, Time과 Cool 갱신
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
  // crnt가 cool보다 작고 timing보다 크면 skill 데미지 들어감
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
  // crnt가 cool과 timing보다 크면 skill 사전 동작 출력
  // -> draw에서 진행
}

// boss의 0번째 skill - 현재 player 위치에 공격 시전
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

// boss의 1번째 skill - monster 자폭
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

// boss의 2번째 skill - boss 주변에 공격
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

// boss의 3번째 skill - map 중앙부분에 강력한 공격
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

// 스킬을 시전하고 시전한 스킬을 사용
void Battle::bossSkill() {
  long long crntTime = timer->getCrntTime();
  // 시전한 스킬 사용
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

  // 스킬 시전
  // 이전에 시전한 스킬과 시간차이가 얼마나지 않으면 시전하지 않음 
  // random하게 값을 정해서 boss가 사용할 skill을 정함
  // 값을 통해서 알맞은 함수를 호출
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

// monster와 player와의 충돌발생시 player가 받는 데미지 설정
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

// boss와 player와의 충돌발생시 player가 받는 데미지 설정
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

// g키를 눌러 다음 stage로 넘어갔을 때의 설정
// monster를 다음 단계로 upgrade시킴
// boss stage 도달 시 보스의 상태를 활성 상태(1)로 변경
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

// 주어진 좌표로 player와의 거리를 구하여 반환
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

// monster가 player와 가까운 위치로 이동
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

// boss가 player와 가까운 위치로 이동
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