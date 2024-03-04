#include "Draw.hpp"

// ������
Draw::Draw() {}

// �Ҹ���
Draw::~Draw() {}

// �ʱ�ȭ
void Draw::Init(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1080, 720);
  glutCreateWindow("Term Project 201902662 �輱��");

  glColor3f(1.0, 1.0, 1.0);
  
  // Texture�� �ʿ��� image�� �θ�
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

  // texture�� ���� ��ü
  sphere = gluNewQuadric();
  gluQuadricTexture(sphere, GL_TRUE);

  // event�� �߻��ϸ� ���� �Լ����� ȣ��
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(NormalKey);
  glutSpecialFunc(SpecialKey);
  glutMainLoop();
}

// draw ����
void Draw::Quit() {}

// game�� ������ ���� ���
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

// player ���, ���� ���¸� Ư�������� ��ȯ
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

// ���� ������ �Է¹޾� ���� ����Ʈ ���
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

// player�� ���� �������� skill�� ���� ���� ������ ���� ����Լ��� ����
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

// monster ���
void Draw::renderMonster(Monster* monster) {
  int x = monster->getPosX();
  int y = monster->getPosY();
  glPushMatrix();
  glTranslatef(x, y, 0);
  glBindTexture(GL_TEXTURE_2D, ids[player->getStage() + 9]);
  glutSolidCube(1.0);
  glPopMatrix();
}

// monster�� ���ݹ����� �Է¹޾� ���� ���ݹ��� ���
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

// ���� stage�� ���� monster�� ���ݹ����� ���� ����Լ��� ����
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

// boss�� 0��° ��ų ���
// ���� ��ġ�� Ư�� ������ ���� ���� ���� ���
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

// boss�� 1��° ��ų ���
// monster�� �����ϱ� �� ���� ������ ���
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

// boss�� 2��° ��ų ���
// boss�� �ֺ��� ���� ���� ���� ���
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

// boss�� 3��° ��ų ���
// map�� ������ ũ�� ��ŭ ���� ���� ���� ���
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

// boss ���
void Draw::renderBoss() {
  int x = boss->getPosX();
  int y = boss->getPosY();
  glPushMatrix();
  glTranslatef(x, y, 1.0);
  glBindTexture(GL_TEXTURE_2D, ids[16]);
  glutSolidCube(3.0);
  glPopMatrix();
}

// �Ͻ� ������� ���
void Draw::renderEclipse() {
  // �¾�
  // �߱�ü ����
  GLfloat light_emission[] = {0.8, 0.0, 0.0, 1.0};
  GLfloat emission_format[] = {0, 0, 0, 1.0};

  glMaterialfv(GL_FRONT, GL_EMISSION, light_emission);

  // �߱�ü�� �ֺ�, Ȯ��, �ݻ籤 ����
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_pos[] = {10, 10, 10, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  // ��ü ǥ���� �ֺ�, Ȯ��, �ݻ籤 ����
  GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat diffuse[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

  // ��ü ���
  glPushMatrix();
  glTranslatef(10, 10, 10);
  glBindTexture(GL_TEXTURE_2D, ids[8]);
  gluSphere(sphere, 2, 10, 10);
  glPopMatrix();

  glMaterialfv(GL_FRONT, GL_EMISSION, emission_format);

  // ��
  // ��ü ǥ���� �ֺ�, Ȯ��, �ݻ籤 ����
  GLfloat ambient1[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat diffuse1[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat specular1[] = {1.0, 1.0, 1.0, 1.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);

  // stage �� ���� ��ǥ ����
  GLfloat moonX = player->getStage() * 5 - 25;
  GLfloat moonY = player->getStage() * 2 - 7;

  // ��ü ���
  glPushMatrix();
  glTranslatef(moonX, moonY, 12.0);
  glBindTexture(GL_TEXTURE_2D, ids[9]);
  gluSphere(sphere, 1.5, 10, 10);
  glPopMatrix();
}

// gameȭ�鿡 ��µǴ� user interface
void Draw::renderUI() {
  string output;
  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  // ���� - ü��, ���ݷ�, ��� ���
  output = "HP " + to_string(player->getHP()) + " / " +
           to_string(player->getFullHP());
  renderBitmapString(19.0, 6.0, &output);
  output = "DMG " + to_string(player->getDMG());
  renderBitmapString(25.0, 0.0, &output);
  output = to_string(player->getGold()) + "g";
  renderBitmapString(22.0, -2.0, &output);

  // �»�� - ���� �� ���� �ʿ� ��� ���
  output = "1.Weapon, 2.Armor, 3.Potion";
  renderBitmapString(-5.0, 30.0, &output);
  output = to_string(player->getWeapon()->getCost()) + ",         " +
           to_string(player->getArmor()->getCost()) + ",         1000 ";
  renderBitmapString(-6.0, 26.0, &output);

  // ��� - ���� stage ���� ���
  if (player->getStage() == 6) {
    output = "Boss";
  } else {
    output = "Stage" + to_string(player->getStage());
  }
  renderBitmapString(14.0, 17.0, &output);

  // ���ϴ� - ��ų key�� ��ų ��Ÿ�� ���
  output = "Q W E R";
  renderBitmapString(-18.0, 0.0, &output);
  output = "";
  for (int i = 0; i < 4; i++) {
    output += to_string(timer->DiffCrnt(player->getSkillCool(i))) + " ";
  }
  renderBitmapString(-16.0, -2.0, &output);

  // ���ϴ� - boss stage�� boss ü�� ���
  if (player->getStage() == 6) {
    output = "Boss HP " + to_string(boss->getHP()) + " / " +
             to_string(boss->getFullHP());
    renderBitmapString(-4.0, -14.0, &output);
  }

  // ��� - boss stage clear �� clear ���� ���
  if (boss->getState() == 0) {
    output = "Clear";
    renderBitmapString(0.0, 0.0, &output);
  }

  glPopMatrix();
}

// ȭ�鿡 ����ϴ� �Լ�
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

// ȭ�� ũ�� ����
void Draw::Reshape(int w, int h) {
  float ratio = w / (float)h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, ratio, 10, 100);
}

// �Ϲ� key�Է� �̺�Ʈ �߻� ó��
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

// Ư�� key�Է� �̺�Ʈ �߻� ó��
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

// ��ǥ�� ���ڿ��� �Է¹޾� ȭ�鿡 ���
void Draw::renderBitmapString(float x, float y, const string* str) {
  glRasterPos2f(x, y);
  for (char c : *str) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
}

// draw ���� �� texture�� �ҷ����� �Լ�
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

// ��� ����
const float Draw::REGULAR_MAX_MAP_SIZE_P = MAX_MAP_SIZE + 0.5;
const float Draw::REGULAR_MAX_MAP_SIZE_M = -MAX_MAP_SIZE + 0.5;