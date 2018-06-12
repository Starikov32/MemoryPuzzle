#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <vector>
#include <array>

class GameBoard
{
public:
  GameBoard() = delete;
  GameBoard(const GameBoard &gameBoard) = delete;
  GameBoard &operator=(const GameBoard &gameBoard) = delete;
  GameBoard(std::size_t width, std::size_t length);
  ~GameBoard() = default;

  void turn(std::size_t index);
  bool isTurned(std::size_t index);

  void guess(std::size_t index);
  bool isGuessed(std::size_t index);

  bool isPair(std::size_t first, std::size_t second);
  bool allGuessed();
  void show();

  // Sizes of board
  const std::size_t WIDTH;
  const std::size_t LENGTH;
  // Sizes of card
  const static std::size_t CARD_WIDTH = 3;
  const static std::size_t CARD_LENGTH = 5;

private:
  // Default card shirt
  const std::vector<std::vector<char>> DEFAULT_PATTERN =
  {
          {'+', '-', '-', '-', '+'},
          {'|', 'C', '+', '+', '|'},
          {'+', '-', '-', '-', '+'},
  };
  // Already guessed cards
  std::vector<bool> guessed;
  // Upside down cards
  std::vector<bool> turned;
  // Array of cards pictures
  std::vector<std::vector<std::vector<char>>> cards;
};

#endif // !GAME_BOARD
