#include <cstdio>
#include <cstdlib>
#include <raylib.h>

#include "config.h"
#include "types.h"
#include "utils.h"

// FIX: character rendering for board

void Update(TicTacToe *game) {
  game->w = GetRenderWidth();
  game->h = GetRenderHeight();
  game->boardLineThickness = game->w / 25;
  game->hudYOffset = game->h / 4;
  game->h1FontSize = game->w / 10;
  game->h2FontSize = game->w / 15;

  if (game->winner != ' ') {
    if (IsKeyPressed(RESTART_KEY)) {
      ResetGame(game);
    }
  } else {
    int tileW = game->w / BOARD_SIZE_AXIS - game->boardLineThickness;
    int tileH = (game->h - game->hudYOffset) / BOARD_SIZE_AXIS -
                game->boardLineThickness;

    for (int y = 0; y < BOARD_SIZE_AXIS; ++y) {
      for (int x = 0; x < BOARD_SIZE_AXIS; ++x) {
        int index = y * BOARD_SIZE_AXIS + x;

        int tileX = x * tileW + x * game->boardLineThickness;
        tileX += game->boardLineThickness / 2;
        int tileY = y * tileH + y * game->boardLineThickness + game->hudYOffset;

        // check if user clicked tile
        if (MouseHovered(tileX, tileY, tileW, tileH) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          if (game->board[index] == ' ') {
            game->board[index] = game->turn;

            game->turn = game->turn == 'X' ? 'O' : 'X';
            CheckWinner(game->board, &game->winner);
            if (game->winner == 'X') {
              game->scoreX++;
            } else if (game->winner == 'O') {
              game->scoreO++;
            }
          }
        }
      }
    }
  }
}

void Draw(TicTacToe *game) {
  BeginDrawing();

  ClearBackground(COLOR_WINDOW_BG);

  if (game->winner == ' ') {
    // draw board
    int tileW = game->w / BOARD_SIZE_AXIS - game->boardLineThickness;
    int tileH = (game->h - game->hudYOffset) / BOARD_SIZE_AXIS -
                game->boardLineThickness;

    int centerY = game->hudYOffset/2-game->h2FontSize/2;
    const char *turn = game->turn == 'X' ? "Turn: X" : "Turn: O";
    int fontSize = AssertTextFitsInDimensions(turn, game->h2FontSize,
            tileW, tileH);
    int turnW = MeasureText(turn, fontSize);
    DrawText(turn, game->boardLineThickness/2 + tileW / 2 - turnW / 2,
            game->hudYOffset/2-fontSize/2, fontSize, COLOR_TEXT_FG);

    char *scoreX = (char*)malloc(sizeof(char)*10);
    sprintf(scoreX, "Score X: %d", game->scoreX);
    fontSize = AssertTextFitsInDimensions(scoreX, game->h2FontSize,
            tileW, tileH);
    int scoreXW = MeasureText(scoreX, fontSize);
    DrawText(scoreX, tileW + game->boardLineThickness + tileW / 2 - scoreXW / 2, centerY,
             fontSize, COLOR_TEXT_FG);

    char *scoreO = (char*)malloc(sizeof(char)*10);
    sprintf(scoreO, "Score O: %d", game->scoreO);
    fontSize = AssertTextFitsInDimensions(scoreO, game->h2FontSize,
            tileW, tileH);
    int scoreOW = MeasureText(scoreO, fontSize);
    DrawText(scoreO, 2 * tileW + 2 * game->boardLineThickness + tileW / 2 - scoreOW / 2, centerY,
            fontSize, COLOR_TEXT_FG);

    free(scoreX);
    free(scoreO);

    for (int y = 0; y < BOARD_SIZE_AXIS; ++y) {
      for (int x = 0; x < BOARD_SIZE_AXIS; ++x) {
        int index = y * BOARD_SIZE_AXIS + x;

        int tileX = x * tileW + x * game->boardLineThickness;
        tileX += game->boardLineThickness / 2;
        int tileY = y * tileH + y * game->boardLineThickness + game->hudYOffset;

        // draw tile
        DrawRectangle(tileX, tileY, tileW, tileH, COLOR_BOARD_TILE);

        // if needed, draw character
        if (game->board[index] != ' ') {
            const char *text = &game->board[index];
          int charW = MeasureText(text, game->h1FontSize);
          int charX = tileX + tileW / 2 - charW / 2;
          int charY = tileY + tileH / 2 - game->h1FontSize / 2;
          DrawText(text, charX, charY, game->h1FontSize,
                   COLOR_FG);
        }
      }
    }
  } else {
    const char *text = game->winner == 'X' ? "Winner: X" : game->winner == 'O' ? "Winner: O" : "Winner: DRAW";
    int textW = MeasureText(text, game->h2FontSize);
    DrawText(text, game->w / 2 - textW / 2, game->h / 2 - game->h2FontSize / 2,
             game->h2FontSize, COLOR_TEXT_FG);
  }

  EndDrawing();
}

int main() {
  TicTacToe game = {0};
  game.w = DEFAULT_WINDOW_WIDTH, game.h = DEFAULT_WINDOW_HEIGHT;
  game.turn = 'X', game.winner = ' ';
  game.scoreX = 0, game.scoreO = 0;
  for (int i = 0; i < sizeof(game.board) / sizeof(char); ++i) {
    game.board[i] = ' ';
  }

  SetConfigFlags(WINDOW_FLAGS);
  InitWindow(game.w, game.h, WINDOW_TITLE);
  SetTargetFPS(TARGET_FPS);
  SetExitKey(EXIT_KEY);

  while (!WindowShouldClose()) {
    Update(&game);
    Draw(&game);
  }

  CloseWindow();
  return 0;
}
