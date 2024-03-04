#include "Equipment.hpp"

// »ı¼ºÀÚ
Equipment::Equipment(int cost,int ability) {
  this->level = 1;
  this->cost = cost;
  this->ability = ability;
}

// getter, setter
int Equipment::getLevel() { return level; }

int Equipment::getCost() { return cost; }

int Equipment::getAbility() { return ability; }

void Equipment::setLevel(int level) { this->level = level; }

void Equipment::setCost(int cost) { this->cost = cost; }

void Equipment::setAbility(int ability) { this->ability = ability; }