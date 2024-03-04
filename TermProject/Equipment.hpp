#pragma once

class Equipment {
 public:
  Equipment(int cost, int ability);

  int getLevel();
  int getCost();
  int getAbility();

  void setLevel(int level);
  void setCost(int cost);
  void setAbility(int ability);

 private:
  int level;
  int cost;
  int ability;
};