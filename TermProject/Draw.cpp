#include "Draw.hpp"

// 생성자
Draw::Draw() {}

// 소멸자
Draw::~Draw() {}

// 초기화
void Draw::Init(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1080, 720);
  glutCreateWindow("Term Project 201902662 김선규");

  glColor3f(1.0, 1.0, 1.0);
  
  // Texture에 필요한 image를 부름
  // 0 background
  
  // 1 ~ 5 monster map
  LoadTexture(1, "texture/grass.bmp");
  LoadTexture(2, "texture/water.bmp");
  LoadTexture(3, "texture/desert.bmp");
  LoadTexture(4, "texture/skin.bmp");
  LoadTexture(5, "texture/earth.bmp");
  // 6 boss map
  LoadTexture(6, "texture/hell.bmp");
  // 7 player
  LoadTexture(7, "texture/snow.bmp");
  // 8 sun
  LoadTexture(8, "texture/sun.bmp");
  // 9 moon
  LoadTexture(9, "texture/moon.bmp");
  // 10 ~ 14 monster
  LoadTexture(10, "texture/chicken.bmp");
  LoadTexture(11, "texture/slime.bmp");
  LoadTexture(12, "texture/lion.bmp");
  LoadTexture(13, "texture/brain.bmp");
  LoadTexture(14, "texture/angel.bmp");
  // 15 boss unit
  LoadTexture(15, "texture/devil.bmp");
  // 16 boss
  LoadTexture(16, "texture/boss.bmp");

  // texture를 붙일 구체
  sphere = gluNewQuadric();
  gluQuadricTexture(sphere, GL_TRUE);

  // event가 발생하면 다음 함수들을 호출
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(NormalKey);
  glutSpecialFunc(SpecialKey);
  glutMainLoop();
}

// draw 종료
void Draw::Quit() {}

// game을 진행할 지형 출력
void Draw::renderMap() {
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, ids[player->getStage()]);
  glBegin(GL_QUADS);
  glVertex3f(REGULAR_MAX_MAP_SIZE_M, REGULAR_MAX_MAP_SIZE_M, -0.5);
  glVertex3f(REGULAR_MAX_MAP_SIZE_P, REGULAR_MAX_MAP_SIZE_M, -0.5);
  glVertex3f(REGULAR_MAX_MAP_SIZE_P, REGULAR_MAX_MAP_SIZE_P, -0.5);
  glVertex3f(REGULAR_MAX_MAP_SIZE_M, REGULAR_MAX_MAP_SIZE_P, -0.5);
  glEnd();
  glPopMatrix();
}

// player 출력, 무적 상태면 특정색으로 변환
void Draw::renderPlayer() {
  int x = player->getPosX();
  int y = player->getPosY();
  glPushMatrix();
  glTranslatef(x, y, 0);
  if (player->getState() == 2) {
    glColor3f(0.0, 1.0, 1.0);
  }
  glBindTexture(GL_TEXTURE_2D, ids[7]);
  glutSolidCube(1.0);
  glPopMatrix();
}

// 공격 범위를 입력받아 공격 이펙트 출력
void Draw::renderPlayerScope(int scope[][5]) {
  float x = player->getPosX() - 2;
  float y = player->getPosY() - 2;
  glPushMatrix();
  glColor3f(0.93, 0.9, 0.76);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (scope[i][j] == 0) continue;
      glBegin(GL_QUADS);
      glVertex2f(x + i - 0.5, y + j + 0.5);
      glVertex2f(x + i + 0.5, y + j + 0.5);
      glVertex2f(x + i + 0.5, y + j - 0.5);
      glVertex2f(x + i - 0.5, y + j - 0.5);
      glEnd();
    }
  }
  glPopMatrix();
}

// player가 현재 실행중인 skill에 따라 공격 범위를 정해 출력함수에 전달
void Draw::renderPlayerSkill() {
  if (draw->getPlayerSkillTiming() < timer->getCrntTime()) return;
  switch (draw->getPlayerCrntSkill()) {
    case 0: {
      int scope[5][5] = {{0, 0, 0, 0, 0},
                         {0, 1, 1, 1, 0},
                         {0, 1, 1, 1, 0},
                         {0, 1, 1, 1, 0},
                         {0, 0, 0, 0, 0}};
      renderPlayerScope(scope);
    } break;
    case 2: {
      int scope[5][5] = {{1, 1, 1, 1, 1},
                         {1, 0, 1, 0, 1},
                         {1, 1, 1, 1, 1},
                         {1, 0, 1, 0, 1},
                         {1, 1, 1, 1, 1}};
      renderPlayerScope(scope);
    } break;
    case 3: {
      int scope[5][5] = {{0, 0, 0, 0, 0},
                         {0, 0, 1, 0, 0},
                         {0, 1, 1, 1, 0},
                         {0, 0, 1, 0, 0},
                         {0, 0, 0, 0, 0}};
      renderPlayerScope(scope);
    } break;
    default:
      break;
  }
}

// monster 출력
void Draw::renderMonster(Monster* monster) {
  int x = monster->getPosX();
  int y = monster->getPosY();
  glPushMatrix();
  glTranslatef(x, y, 0);
  glBindTexture(GL_TEXTURE_2D, ids[player->getStage() + 9]);
  glutSolidCube(1.0);
  glPopMatrix();
}

// monster의 공격범위를 입력받아 사전 공격범위 출력
void Draw::renderMonsterScope(int scope[][5], Monster* monster) {
  float x = monster->getPosX() - 2;
  float y = monster->getPosY() - 2;
  glPushMatrix();
  glColor3f(1.0, 0.0, 0.0);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (scope[i][j] == 0) continue;
      glBegin(GL_QUADS);
      glVertex2f(x + i - 0.5, y + j + 0.5);
      glVertex2f(x + i + 0.5, y + j + 0.5);
      glVertex2f(x + i + 0.5, y + j - 0.5);
      glVertex2f(x + i - 0.5, y + j - 0.5);
      glEnd();
    }
  }
  glPopMatrix();
}

// 현재 stage에 따라 monster의 공격범위를 정해 출력함수에 전달
void Draw::renderMonsterSkill(Monster* monster) {
  long long crntTime = timer->getCrntTime();
  long long skillCool = monster->getSkillCool();
  long long skillTiming = monster->getSkillTiming();
  if (skillTiming > crntTime && skillCool != skillTiming) {
    switch (player->getStage()) {
      case 1: {
        int scope[][5] = {{0, 0, 0, 0, 0},
                          {0, 0, 1, 0, 0},
                          {0, 1, 1, 1, 0},
                          {0, 0, 1, 0, 0},
                          {0, 0, 0, 0, 0}};
        renderMonsterScope(scope, monster);
      } break;
      case 2: {
        int scope[][5] = {{0, 0, 0, 0, 0},
                          {0, 1, 1, 1, 0},
                          {0, 1, 1, 1, 0},
                          {0, 1, 1, 1, 0},
                          {0, 0, 0, 0, 0}};
        renderMonsterScope(scope, monster);
      } break;
      case 3: {
        int scope[][5] = {{0, 1, 0, 1, 0},
                          {1, 1, 1, 1, 1},
                          {0, 1, 1, 1, 0},
                          {1, 1, 1, 1, 1},
                          {0, 1, 0, 1, 0}};
        renderMonsterScope(scope, monster);
      } break;
      case 4: {
        int scope[][5] = {{1, 0, 1, 0, 1},
                          {0, 1, 1, 1, 0},
                          {1, 1, 1, 1, 1},
                          {0, 1, 1, 1, 0},
                          {1, 0, 1, 0, 1}};
        renderMonsterScope(scope, monster);
      } break;
      case 5: {
        int scope[][5] = {{1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1}};
        renderMonsterScope(scope, monster);
      } break;
      default:
        break;
    }
  }
}

// boss의 0번째 스킬 출력
// 공격 위치에 특정 범위의 사전 공격 범위 출력
void Draw::renderBossSkill0() {
  long long crntTime = timer->getCrntTime();
  long long skillCool = boss->getSkillCool(0);
  long long skillTiming = boss->getSkillTiming(0);
  if (skillTiming <= crntTime || skillCool == skillTiming) return;

  float x = boss->getTargetX(0) - 1;
  float y = boss->getTargetY(0) - 1;
  glPushMatrix();
  glColor3f(1.0, 0.0, 0.0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      glBegin(GL_QUADS);
      glVertex2f(x + i - 0.5, y + j + 0.5);
      glVertex2f(x + i + 0.5, y + j + 0.5);
      glVertex2f(x + i + 0.5, y + j - 0.5);
      glVertex2f(x + i - 0.5, y + j - 0.5);
      glEnd();
    }
  }
  glPopMatrix();
}

// boss의 1번째 스킬 출력
// monster가 자폭하기 전 폭발 범위를 출력
void Draw::renderBossSkill1() {
  long long crntTime = timer->getCrntTime();
  long long skillCool = boss->getSkillCool(1);
  long long skillTiming = boss->getSkillTiming(1);
  if (skillTiming <= crntTime || skillCool == skillTiming) return;

  list<Monster*>::iterator It;
  list<Monster*>* monsterList = game->getMonsterList();
  for (It = (*monsterList).begin(); It != (*monsterList).end(); ++It) {
    if ((*It)->getState() == 0) continue;
    float x = (*It)->getPosX() - 1;
    float y = (*It)->getPosY() - 1;
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        glBegin(GL_QUADS);
        glVertex2f(x + i - 0.5, y + j + 0.5);
        glVertex2f(x + i + 0.5, y + j + 0.5);
        glVertex2f(x + i + 0.5, y + j - 0.5);
        glVertex2f(x + i - 0.5, y + j - 0.5);
        glEnd();
      }
    }
    glPopMatrix();
  }
}

// boss의 2번째 스킬 출력
// boss의 주변에 사전 공격 범위 출력
void Draw::renderBossSkill2() {
  long long crntTime = timer->getCrntTime();
  long long skillCool = boss->getSkillCool(2);
  long long skillTiming = boss->getSkillTiming(2);
  if (skillTiming <= crntTime || skillCool == skillTiming) return;

  float x = boss->getPosX() - 4;
  float y = boss->getPosY() - 4;
  glPushMatrix();
  glColor3f(1.0, 0.0, 0.0);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      glBegin(GL_QUADS);
      glVertex2f(x + i - 0.5, y + j + 0.5);
      glVertex2f(x + i + 0.5, y + j + 0.5);
      glVertex2f(x + i + 0.5, y + j - 0.5);
      glVertex2f(x + i - 0.5, y + j - 0.5);
      glEnd();
    }
  }
  glPopMatrix();
}

// boss의 3번째 스킬 출력
// map에 정해진 크기 만큼 사전 공격 범위 출력
void Draw::renderBossSkill3() {
  long long crntTime = timer->getCrntTime();
  long long skillCool = boss->getSkillCool(3);
  long long skillTiming = boss->getSkillTiming(3);
  if (skillTiming <= crntTime || skillCool == skillTiming) return;

  glPushMatrix();
  glColor3f(1.0, 0.0, 0.0);
  for (int i = -10; i < 12; i++) {
    for (int j = -10; j < 12; j++) {
      glBegin(GL_QUADS);
      glVertex2f(i - 0.5, j + 0.5);
      glVertex2f(i + 0.5, j + 0.5);
      glVertex2f(i + 0.5, j - 0.5);
      glVertex2f(i - 0.5, j - 0.5);
      glEnd();
    }
  }
  glPopMatrix();
}

// boss 출력
void Draw::renderBoss() {
  int x = boss->getPosX();
  int y = boss->getPosY();
  glPushMatrix();
  glTranslatef(x, y, 1.0);
  glBindTexture(GL_TEXTURE_2D, ids[16]);
  glutSolidCube(3.0);
  glPopMatrix();
}

// 일식 진행과정 출력
void Draw::renderEclipse() {
  // 태양
  // 발광체 설정
  GLfloat light_emission[] = {0.8, 0.0, 0.0, 1.0};
  GLfloat emission_format[] = {0, 0, 0, 1.0};

  glMaterialfv(GL_FRONT, GL_EMISSION, light_emission);

  // 발광체의 주변, 확산, 반사광 설정
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_pos[] = {10, 10, 10, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  // 구체 표면의 주변, 확산, 반사광 설정
  GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat diffuse[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

  // 구체 출력
  glPushMatrix();
  glTranslatef(10, 10, 10);
  glBindTexture(GL_TEXTURE_2D, ids[8]);
  gluSphere(sphere, 2, 10, 10);
  glPopMatrix();

  glMaterialfv(GL_FRONT, GL_EMISSION, emission_format);

  // 달
  // 구체 표면의 주변, 확산, 반사광 설정
  GLfloat ambient1[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat diffuse1[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat specular1[] = {1.0, 1.0, 1.0, 1.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);

  // stage 별 달의 좌표 설정
  GLfloat moonX = player->getStage() * 5 - 25;
  GLfloat moonY = player->getStage() * 2 - 7;

  // 구체 출력
  glPushMatrix();
  glTranslatef(moonX, moonY, 12.0);
  glBindTexture(GL_TEXTURE_2D, ids[9]);
  gluSphere(sphere, 1.5, 10, 10);
  glPopMatrix();
}

// game화면에 출력되는 user interface
void Draw::renderUI() {
  string output;
  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  // 우상단 - 체력, 공격력, 골드 출력
  output = "HP " + to_string(player->getHP()) + " / " +
           to_string(player->getFullHP());
  renderBitmapString(19.0, 6.0, &output);
  output = "DMG " + to_string(player->getDMG());
  renderBitmapString(25.0, 0.0, &output);
  output = to_string(player->getGold()) + "g";
  renderBitmapString(22.0, -2.0, &output);

  // 좌상단 - 상점 및 구매 필요 골드 출력
  output = "1.Weapon, 2.Armor, 3.Potion";
  renderBitmapString(-5.0, 30.0, &output);
  output = to_string(player->getWeapon()->getCost()) + ",         " +
           to_string(player->getArmor()->getCost()) + ",         1000 ";
  renderBitmapString(-6.0, 26.0, &output);

  // 상단 - 현재 stage 정보 출력
  if (player->getStage() == 6) {
    output = "Boss";
  } else {
    output = "Stage" + to_string(player->getStage());
  }
  renderBitmapString(14.0, 17.0, &output);

  // 좌하단 - 스킬 key와 스킬 쿨타임 출력
  output = "Q W E R";
  renderBitmapString(-18.0, 0.0, &output);
  output = "";
  for (int i = 0; i < 4; i++) {
    output += to_string(timer->DiffCrnt(player->getSkillCool(i))) + " ";
  }
  renderBitmapString(-16.0, -2.0, &output);

  // 우하단 - boss stage면 boss 체력 출력
  if (player->getStage() == 6) {
    output = "Boss HP " + to_string(boss->getHP()) + " / " +
             to_string(boss->getFullHP());
    renderBitmapString(-4.0, -14.0, &output);
  }

  // 가운데 - boss stage clear 시 clear 문구 출력
  if (boss->getState() == 0) {
    output = "Clear";
    renderBitmapString(0.0, 0.0, &output);
  }

  glPopMatrix();
}

// 화면에 출력하는 함수
void Draw::Display() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-25.0, -25.0, 25.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  // Texture Init
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

  GLfloat plane_coef_s0[] = {1.0, 0.0, 0.0, 1.0};
  GLfloat plane_coef_t0[] = {0.0, 1.0, 0.0, 1.0};
  glTexGenfv(GL_S, GL_OBJECT_PLANE, plane_coef_s0);
  glTexGenfv(GL_T, GL_OBJECT_PLANE, plane_coef_t0);

  // Lighting Init
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // lighting & texture
  draw->renderEclipse();

  // not boss satge disable texture
  if (player->getStage() != 6) {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
  } else {
    // boss stage lighting
    GLfloat ambient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat diffuse[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat specular[] = {0.5, 0.5, 0.5, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  }

  // only texture mapping
  // texture about map
  GLfloat plane_coef_s1[] = {0.05, 0.0, 0.0, 1.0};
  GLfloat plane_coef_t1[] = {0.0, 0.05, 0.0, 1.0};
  glTexGenfv(GL_S, GL_OBJECT_PLANE, plane_coef_s1);
  glTexGenfv(GL_T, GL_OBJECT_PLANE, plane_coef_t1);

  draw->renderMap();

  // texture about unit
  GLfloat plane_coef_s2[] = {5.0, 0.0, 0.0, 1.0};
  GLfloat plane_coef_t2[] = {0.0, 5.0, 0.0, 1.0};
  glTexGenfv(GL_S, GL_OBJECT_PLANE, plane_coef_s2);
  glTexGenfv(GL_T, GL_OBJECT_PLANE, plane_coef_t2);

  list<Monster*>::iterator It;
  list<Monster*>* monsterList = game->getMonsterList();
  for (It = (*monsterList).begin(); It != (*monsterList).end(); ++It) {
    if ((*It)->getState() == 0) continue;
    draw->renderMonster(*It);
  }
  if (boss->getState() == 1) draw->renderBoss();
  draw->renderPlayer();

  // boos stage disable texture
  if (player->getStage() == 6) {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
  }

  // disable texture
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_TEXTURE_2D);

  // don't use texture
  // print Unit's skill
  draw->renderPlayerSkill();
  monsterList = game->getMonsterList();
  for (It = (*monsterList).begin(); It != (*monsterList).end(); ++It) {
    if ((*It)->getState() == 0) continue;
    draw->renderMonsterSkill(*It);
  }
  if (boss->getState() == 1) {
    draw->renderBossSkill0();
    draw->renderBossSkill1();
    draw->renderBossSkill2();
    draw->renderBossSkill3();
  }

  // disable depth
  glDisable(GL_DEPTH_TEST);

  // print user interface
  draw->renderUI();

  glutPostRedisplay();
  glFlush();
}

// 화면 크기 조정
void Draw::Reshape(int w, int h) {
  float ratio = w / (float)h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, ratio, 10, 100);
}

// 일반 key입력 이벤트 발생 처리
void Draw::NormalKey(unsigned char key, int x, int y) {
  if (player->getState() == 0) return;
  long long crntTime = timer->getCrntTime();
  switch (key) {
    case '1':
      player->buyWeapon();
      break;
    case '2':
      player->buyArmor();
      break;
    case '3':
      player->drink();
      break;
    case 'q':
      if (battle->playerSkill(0)) {
        draw->setPlayerCrntSkill(0);
        draw->setPlayerSkillTiming(crntTime + 100);
      }
      break;
    case 'w':
      battle->playerSkill(1);
      break;
    case 'e':
      if (battle->playerSkill(2)) {
        draw->setPlayerCrntSkill(2);
        draw->setPlayerSkillTiming(crntTime + 300);
      }
      break;
    case 'r':
      if (battle->playerSkill(3)) {
        draw->setPlayerCrntSkill(3);
        draw->setPlayerSkillTiming(crntTime + 500);
      }
      break;
    case 'g':
      battle->nextStage();
      break;
    default:
      break;
  }
}

// 특수 key입력 이벤트 발생 처리
void Draw::SpecialKey(int key, int x, int y) {
  if (player->getState() == 0) return;
  int posX = player->getPosX();
  int posY = player->getPosY();
  switch (key) {
    case GLUT_KEY_UP:
      if (posX < MAX_MAP_SIZE) player->setPosX(posX + 1);
      break;
    case GLUT_KEY_DOWN:
      if (posX - 1 > -MAX_MAP_SIZE) player->setPosX(posX - 1);
      break;
    case GLUT_KEY_LEFT:
      if (posY < MAX_MAP_SIZE) player->setPosY(posY + 1);
      break;
    case GLUT_KEY_RIGHT:
      if (posY - 1 > -MAX_MAP_SIZE) player->setPosY(posY - 1);
      break;
    default:
      break;
  }
}

// 좌표와 문자열을 입력받아 화면에 출력
void Draw::renderBitmapString(float x, float y, const string* str) {
  glRasterPos2f(x, y);
  for (char c : *str) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
}

// draw 시작 전 texture를 불러오는 함수
void Draw::LoadTexture(int idx, const char* filename) {
  tex[idx] = auxDIBImageLoad(filename);

  glGenTextures(17, &ids[idx]);
  glBindTexture(GL_TEXTURE_2D, ids[idx]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[idx]->sizeX, tex[idx]->sizeY, 0, GL_RGB,
               GL_UNSIGNED_BYTE, tex[idx]->data);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// getter, setter
int Draw::getPlayerCrntSkill() { return playerCrntSkill; }

long long Draw::getPlayerSkillTiming() { return playerSkillTiming; }

void Draw::setPlayerCrntSkill(int playerCrntSkill) {
  this->playerCrntSkill = playerCrntSkill;
}
void Draw::setPlayerSkillTiming(long long playerSkillTiming) {
  this->playerSkillTiming = playerSkillTiming;
}

// 상수 설정
const float Draw::REGULAR_MAX_MAP_SIZE_P = MAX_MAP_SIZE + 0.5;
const float Draw::REGULAR_MAX_MAP_SIZE_M = -MAX_MAP_SIZE + 0.5;