#pragma once

#include <cstdio>
#include <raylib.h>
#include <vector>

#include "config.h"
#include "types.h"

bool MouseHovered(int x, int y, int w, int h) {
  Vector2 mousePos = GetMousePosition();
  return mousePos.x >= x && mousePos.x <= x + w && mousePos.y >= y &&
         mousePos.y <= y + h;
}

std::vector<int> CheckWinner(char board[], char *winner) {
  // Horizontal
  std::vector<int> resX, resO;
  for (int y = 0; y < BOARD_SIZE_AXIS; ++y) {
    int foundXtimes = 0, foundOTimes = 0;
    for (int x = 0; x < BOARD_SIZE_AXIS; ++x) {
      int index = y * BOARD_SIZE_AXIS + x;
      if (board[index] == 'X') {
        foundXtimes++;
        resX.push_back(index);
      } else if (board[index] == 'O') {
        foundOTimes++;
        resO.push_back(index);
      }
    }
    if (foundXtimes == BOARD_SIZE_AXIS) {
      *winner = 'X';
      return resX;
    } else if (foundOTimes == BOARD_SIZE_AXIS) {
      *winner = 'O';
      return resO;
    }
  }

  resX.clear();
  resO.clear();

  // Vertical
  for (int x = 0; x < BOARD_SIZE_AXIS; ++x) {
    int foundXtimes = 0, foundOTimes = 0;
    for (int y = 0; y < BOARD_SIZE_AXIS; ++y) {
      int index = y * BOARD_SIZE_AXIS + x;
      if (board[index] == 'X') {
        foundXtimes++;
          resX.push_back(index);
      } else if (board[index] == 'O') {
        foundOTimes++;
        resO.push_back(index);
      }
    }
    if (foundXtimes == BOARD_SIZE_AXIS) {
      *winner = 'X';
      return resX;
    } else if (foundOTimes == BOARD_SIZE_AXIS) {
      *winner = 'O';
      return resO;
    }
  }

  resX.clear();
  resO.clear();

  // Diagonal
  int foundXtimes = 0, foundOTimes = 0;
  for (int y = 0; y < BOARD_SIZE_AXIS; ++y) {
    for (int x = 0; x < BOARD_SIZE_AXIS; ++x) {
      int index = y * BOARD_SIZE_AXIS + x;
      if (x == y) {
        if (board[index] == 'X') {
          foundXtimes++;
          resX.push_back(index);
        } else if (board[index] == 'O') {
          foundOTimes++;
          resO.push_back(index);
        }
      }
    }
    if (foundXtimes == BOARD_SIZE_AXIS) {
      *winner = 'X';
      return resX;
    } else if (foundOTimes == BOARD_SIZE_AXIS) {
      *winner = 'O';
      return resO;
    }
  }

    resX.clear();
    resO.clear();

  // Diagonal 2
  foundXtimes = 0, foundOTimes = 0;
  for (int y = 0; y < BOARD_SIZE_AXIS; ++y) {
    for (int x = 0; x < BOARD_SIZE_AXIS; ++x) {
      int index = y * BOARD_SIZE_AXIS + x;
      if (x + y == BOARD_SIZE_AXIS - 1) {
        if (board[index] == 'X') {
          foundXtimes++;
          resX.push_back(index);
        } else if (board[index] == 'O') {
          foundOTimes++;
          resO.push_back(index);
        }
      }
    }
    if (foundXtimes == BOARD_SIZE_AXIS) {
      *winner = 'X';
      return resX;
    } else if (foundOTimes == BOARD_SIZE_AXIS) {
      *winner = 'O';
      return resO;
    }
  }

  // Check for draw
  int sum = 0;
  for (int i = 0; i < BOARD_SIZE_AXIS * BOARD_SIZE_AXIS; ++i) {
    if (board[i] == ' ') {
      sum++;
    }
  }
  if (sum == 0) {
    *winner = 'D';
  }

  resX.clear();
  resO.clear();
  return resX;
}

void ResetGame(TicTacToe *game) {
  game->turn =
      game->winner == 'X' ? 'X' : game->winner = 'O' ? 'O' : STARTING_TURN;
  game->winner = ' ';
  for (int i = 0; i < sizeof(game->board) / sizeof(char); ++i) {
    game->board[i] = ' ';
  }
  game->hintTimer = HINT_TIME;
  game->hints.clear();
}

int AssertTextFitsInDimensions(const char *text, int fontSize, int w, int h) {
  int textW = MeasureText(text, fontSize);
  while (textW > w || fontSize > h) {
    fontSize--;
    textW = MeasureText(text, fontSize);
  }
  return fontSize;
}

bool ToHintTile(std::vector<int> hints, int index) {
  for (int i = 0; i < hints.size(); ++i) {
    if (hints[i] == index) {
      return true;
    }
  }
  return false;
}
