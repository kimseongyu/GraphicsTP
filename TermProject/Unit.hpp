#pragma once

class Unit {
 public:
  Unit();
  ~Unit();

  virtual void Init() = 0;
  virtual void Reset() = 0;
  virtual void Update() = 0;

  virtual void birth() = 0;
  virtual void death() = 0;

  int getPosX(), getPosY();
  const char* getName();
  int getHP();
  int getFullHP();
  int getDMG();
  int getGold();
  int getState();
  long long getSpawnTime();
  long long getGenTime();

  void setPosX(int posX), setPosY(int posY);
  void setName(const char* name);
  void setHP(int hp);
  void setFullHP(int fullHP);
  void setDMG(int dmg);
  void setGold(int gold);
  void setState(int state);
  void setSpawnTime(long long spawnTime);
  void setGenTime(long long genTime);

 protected:
  // Unit�� ��ǥ
  int posX, posY;
  // Unit�� �̸�
  const char* name;
  // Unit�� �⺻���� data
  int hp;
  int fullHP;
  int dmg;
  int gold;
  int state;
  // Unit�� ��Ȱ�ϴ� �ð�
  long long spawnTime;
  // Unit�� ��Ȱ�� �ɸ��� �ð�
  long long genTime;
};