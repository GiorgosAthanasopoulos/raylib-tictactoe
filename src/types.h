#pragma once

#include <raylib.h>
#include <vector>

#include "config.h"

typedef struct {
    int w, h;
    int boardLineThickness, hudYOffset;
    int h1FontSize, h2FontSize;

    char turn, winner, board[BOARD_SIZE_AXIS * BOARD_SIZE_AXIS];
    int scoreX, scoreO;

    float hintTimer;
    std::vector<int> hints;
} TicTacToe;
