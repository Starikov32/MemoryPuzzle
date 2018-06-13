#include "../include/game_control.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>

// Cleaning the console ( for Windows and Linux )
void clearScreen();
// Erase input from errors and invalid input
void clearInput();

void GameControl::startMenu()
{
    clearScreen();
    std::cout << "#   # #### #   # ##### #### #   # . #### #  # #### #### #    ####\n"
              << "## ## #    ## ## #   # #  #  # #  . #  # #  #   ##   ## #    #   \n"
              << "# # # #### # # # #   # ####   #   . #### #  #  ##   ##  #    ####\n"
              << "#   # #    #   # #   # # #    #   . #    #  # ##   ##   #    #   \n"
              << "#   # #### #   # ##### #  #   #   . #    #### #### #### #### ####\n";

    // Show game menu
    unsigned int selection;
    enum class MenuItems
    {
        START_GAME,
        EXIT
    };
    do
    {
        std::cout << "\nGame menu ( To select, enter 1 or 2 )\n"
                  << std::setw(5) << "1. "
                  << "Start game\n"
                  << std::setw(5) << "2. "
                  << "Exit\n"
                  << ">> ";
        std::cin >> selection;
        clearInput();
        selection--;
    } while (selection > 1);

    switch ((MenuItems)selection)
    {
    case MenuItems::START_GAME:
        startGame();
        break;
    case MenuItems::EXIT:
        exitGame();
        break;
    default:
        break;
    }
}

// Cleaning the console ( for Windows and Linux )
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif // _WIN32
}

// Erase input from errors and invalid input
void clearInput()
{
    std::cin.clear();
    std::cin.sync();
}

void GameControl::exitGame()
{
    clearScreen();
    std::cout << "Thanks for the game!";
}

void GameControl::startGame()
{
    clearScreen();
    unsigned int selection;
    enum class Level
    {
        EASY,
        NORMAL,
        HARD
    };
    do
    {
        std::cout << "\nPlease choose difficulty level ( To select, enter 1, 2 or 3 )\n"
                  << std::setw(5) << "1. "
                  << "Easy\n"
                  << std::setw(5) << "2. "
                  << "Normal\n"
                  << std::setw(5) << "3. "
                  << "Hard\n"
                  << ">> ";
        std::cin >> selection;
        clearInput();
        selection--;
    } while (selection > 2);

    switch ((Level)selection)
    {
    case Level::EASY:
        gameBoard = std::unique_ptr<GameBoard>(new GameBoard(3, 4));
        break;
    case Level::NORMAL:
        gameBoard = std::unique_ptr<GameBoard>(new GameBoard(4, 4));
        break;
    case Level::HARD:
        gameBoard = std::unique_ptr<GameBoard>(new GameBoard(4, 5));
        break;
    default:
        break;
    }

    while (!gameBoard->allGuessed())
    {
        nextTurn();
    }
    // Show the result of the game
    std::cout << "Excellent! You Won!\n"
              << "Number of you steps = " << numberOfSteps << '\n';
    system("pause");
    startMenu();
}

void GameControl::nextTurn()
{
    clearScreen();
    gameBoard->show();
    std::size_t row;
    std::size_t column;
    std::cout << "Enter coordinates of first card:\n";
    std::size_t firstChoice;
    do
    {
        do
        {
            std::cout << "row ( 1 - " << gameBoard->WIDTH << " ) : ";
            std::cin >> row;
            clearInput();
            row--;
        } while (row > gameBoard->WIDTH - 1);
        do
        {
            std::cout << "column ( 1 - " << gameBoard->LENGTH << " ) : ";
            std::cin >> column;
            clearInput();
            column--;
        } while (column > gameBoard->LENGTH - 1);
        // Calculate the array index from matrix indices
        firstChoice = (row * (gameBoard->LENGTH)) + column;

        if (gameBoard->isGuessed(firstChoice))
        {
            std::cout << "You already guessed this card!\nRe-enter:\n";
        }
        else
        {
            break;
        }
    } while (true);
    gameBoard->turn(firstChoice);
    gameBoard->show();

    std::cout << "Enter coordinates of second card:\n";
    std::size_t secondChoice;
    do
    {
        do
        {
            std::cout << "row ( 1 - " << gameBoard->WIDTH << " ) : ";
            std::cin >> row;
            clearInput();
            row--;
        } while (row > gameBoard->WIDTH - 1);
        do
        {
            std::cout << "column ( 1 - " << gameBoard->LENGTH << " ) : ";
            std::cin >> column;
            clearInput();
            column--;
        } while (column > gameBoard->LENGTH - 1);
        // Calculate the array index from matrix indices
        secondChoice = (row * (gameBoard->LENGTH)) + column;

        if (gameBoard->isGuessed(secondChoice))
        {
            std::cout << "You already guessed this card!\nRe-enter:\n";
        }
        else if (gameBoard->isTurned(secondChoice))
        {
            std::cout << "You already turned this card!\nRe-enter:\n";
        }
        else
        {
            break;
        }
    } while (true);
    gameBoard->turn(secondChoice);
    gameBoard->show();

    if (gameBoard->isPair(firstChoice, secondChoice))
    {
        std::cout << "You are guessed!\n";
        gameBoard->guess(firstChoice);
        gameBoard->guess(secondChoice);
    }
    else
    {
        std::cout << "You are mistaken!\n";
        gameBoard->turn(firstChoice);
        gameBoard->turn(secondChoice);
    }
    system("pause");
    numberOfSteps++;
}