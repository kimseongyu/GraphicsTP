#include <iostream>

#include "Game.hpp"

using namespace std;

int main(int argc, char** argv) {
  // game 준비
  game->Init();
  // thread 처리를 해주어 게임 실행과 동시에 그래픽 처리를 병행
  thread drawThread([argc, argv]() { draw->Init(argc, argv); });
  // game 시작
  game->Run();
  // game 종료 및 삭제
  game->Quit();
  game->Del();
  return 0;
}