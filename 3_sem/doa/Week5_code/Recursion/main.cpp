// Recursion.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include "maze.h"
#include "recursion.h"
#include <iostream>
#include <vector>

// constexpr auto ROWS = 5;
// constexpr auto COLS = 5;

int main() {
  std::cout << "Hello World!\n";

  Array a(6);
  std::cout << "Inserting 0...5\n";
  for (int i = 0; i < 6; i++) {
    a.insert(i);
  }
  std::cout << "Contains 3? (1 for yes, 0 for no): " << a.contains(3)
            << std::endl;
  std::cout << "Contains 6? (1 for yes, 0 for no): " << a.contains(6)
            << std::endl;
  a.minMax();

  std::vector<std::vector<char>> maze = {{'X', 'X', 'X', 'X', 'X', ' '},
                                         {'X', ' ', ' ', ' ', ' ', ' '},
                                         {'X', ' ', 'X', ' ', 'X', ' '},
                                         {'X', ' ', 'X', ' ', 'X', ' '},
                                         {'X', 'E', 'X', ' ', 'X', ' '}};

  MazeSolver solver(maze);

  if (solver.solveMaze(maze, 0, 4)) {
    std::cout << "Path to exit found!\nMaze size: " << maze.size() << std::endl;
  } else {
    std::cout << "No path to exit found.\nMaze size: " << maze.size()
              << std::endl;
  }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
