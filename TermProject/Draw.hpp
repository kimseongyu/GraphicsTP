#pragma once
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <glut.h>
#include <glaux.h>

#include <list>
#include <string>
#include <format>
#include "Game.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Boss.hpp"
#include "Singleton.hpp"

using namespace std;

#define draw Draw::Get()

class Draw : public Singleton<Draw> {
 public:
  Draw();
  ~Draw();

  void Init(int argc, char** argv);
  void Quit();

 private:
  void renderMap();
  void renderPlayer();
  void renderPlayerScope(int scope[][5]);
  void renderPlayerSkill();

  void renderMonster(Monster* monster);
  void renderMonsterScope(int scope[][5], Monster* monster);
  void renderMonsterSkill(Monster* monster);

  void renderBossSkill0();
  void renderBossSkill1();
  void renderBossSkill2();
  void renderBossSkill3();
  void renderBoss();

  void renderEclipse();
  void renderUI();

  static void Display();
  static void Reshape(int w, int h);
  static void NormalKey(unsigned char key, int x, int y);
  static void SpecialKey(int key, int x, int y);

  void renderBitmapString(float x, float y, const string* str);
  void LoadTexture(int num, const char* fileName);

  int getPlayerCrntSkill();
  long long getPlayerSkillTiming();

  void setPlayerCrntSkill(int playerCrntSkill);
  void setPlayerSkillTiming(long long playerSkillTiming);

  unsigned int ids[17];
  AUX_RGBImageRec* tex[17];
  GLUquadric* sphere;

  int playerCrntSkill;
  long long playerSkillTiming;

  static const int MAX_MAP_SIZE = 13;
  static const float REGULAR_MAX_MAP_SIZE_P;
  static const float REGULAR_MAX_MAP_SIZE_M;
};