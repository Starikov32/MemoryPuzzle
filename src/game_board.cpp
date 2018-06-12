#include "../include/game_board.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

GameBoard::GameBoard(std::size_t width, std::size_t length) : WIDTH(width), LENGTH(length)
{
    srand(time(nullptr));
    // Calculating the number of cards and the number of pairs
    const std::size_t numberOfCards = WIDTH * LENGTH;
    const std::size_t numberOfPairs = numberOfCards / 2;
    // Mark everything as unguessed and not turned
    turned = std::vector<bool>(numberOfCards, false);
    guessed = std::vector<bool>(numberOfCards, false);
    // Creating drawings and mixing them
    for (std::size_t i = 0; i < numberOfPairs; ++i)
    {
        char picture = (char(i + 33));
        std::vector<std::vector<char>> card =
            {
                {'#', '-', '-',     '-', '#'},
                {'|', ' ', picture, ' ', '|'},
                {'#', '-', '-',     '-', '#'}
            };
        cards.push_back(card);
        cards.push_back(card);
    }
    std::random_shuffle(cards.begin(), cards.end());
}

void GameBoard::turn(std::size_t index)
{
    turned[index] = !turned[index];
}

bool GameBoard::isTurned(std::size_t index)
{
    return turned[index];
}

void GameBoard::guess(std::size_t index)
{
    guessed[index] = true;
}

bool GameBoard::isGuessed(std::size_t index)
{
    return guessed[index];
}

bool GameBoard::isPair(std::size_t first, std::size_t second)
{
    return (cards[first] == cards[second]);
}

bool GameBoard::allGuessed()
{
    return std::all_of(guessed.begin(), guessed.end(), [](bool x) { return x; });
}

void GameBoard::show()
{
    // Here the matrix of matrices is printed.
    // There is a matrix of cards.
    // And each card is a matrix of symbols.
    for(std::size_t row = 0; row < WIDTH; ++row)
    {
        for(std::size_t internalRow = 0; internalRow < CARD_WIDTH; ++internalRow)
        {
            for(std::size_t column = 0; column < LENGTH; ++column)
            {
                // Calculate the array index from matrix indices
                std::size_t cardIndex = (row * LENGTH) + column;
                for(std::size_t internalColumn = 0; internalColumn < CARD_LENGTH; ++internalColumn)
                {
                    if(guessed[cardIndex] || turned[cardIndex])
                    {
                        std::cout << cards[cardIndex][internalRow][internalColumn];
                    }
                    else
                    {
                        std::cout << DEFAULT_PATTERN[internalRow][internalColumn];
                    }
                }
                std::cout << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
}