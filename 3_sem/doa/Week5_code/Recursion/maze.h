#pragma once
#include <iostream>
#include <vector>

class MazeSolver {
public:
  MazeSolver(std::vector<std::vector<char> > maze) {
    visited.resize(maze.size(),
                   std::vector<bool>(
                       maze[0].size(),
                       false)); // Resize the visited array to match maze size
  }
  void reset() {
    visited.resize(
        visited.size(),
        std::vector<bool>(visited[0].size(),
                          false)); // reset the maze solver not necessary
  }

  bool solveMaze(std::vector<std::vector<char> > &maze, int row,
                 int col) { // input, vect<vect<char>> med row og col start

    // Base cases: out of bounds or obstacle or already visited
    if (row < 0 || row >= maze.size() || col < 0 || col >= maze[0].size() ||
        maze[row][col] == 'X' || visited[row][col]) {
      return false;
    }

    // Found the exit
    if (maze[row][col] == 'E') {
      return true;
    }

    // Mark current position as visited
    visited[row][col] = true;

    // Explore adjacent positions recursively
    if (solveMaze(maze, row + 1, col) || solveMaze(maze, row - 1, col) ||
        solveMaze(maze, row, col + 1) || solveMaze(maze, row, col - 1)) {
      return true;
    }

    // No path found from this position, backtrack
    visited[row][col] = false;
    return false;
  }

private:
  std::vector<std::vector<bool> > visited; // To keep track of visited positions
};
