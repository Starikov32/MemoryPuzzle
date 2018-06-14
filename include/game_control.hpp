#ifndef GAME_CONTROL_HPP
#define GAME_CONTROL_HPP

#include "../include/game_board.hpp"
#include <memory>

class GameControl
{
public:
  GameControl() = default;
  ~GameControl() = default;

  void startMenu();
  void startGame();
  void nextTurn();

private:
  std::size_t numberOfSteps = 0;
  std::unique_ptr<GameBoard> gameBoard;
};

#endif // !GAME_CONTROL
