#include <iostream>

#include "Game.hpp"

using namespace std;

int main(int argc, char** argv) {
  // game �غ�
  game->Init();
  // thread ó���� ���־� ���� ����� ���ÿ� �׷��� ó���� ����
  thread drawThread([argc, argv]() { draw->Init(argc, argv); });
  // game ����
  game->Run();
  // game ���� �� ����
  game->Quit();
  game->Del();
  return 0;
}