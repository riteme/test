//
// Copyright 2015 riteme
//

#ifndef PROJECT_LIBGAME_GAME_H_
#define PROJECT_LIBGAME_GAME_H_

#include <SDL2/SDL.h>

// some marcos
#define GAME_SUCCESS 0
#define GAME_FAILURE -1

// defaults
#define WND_TITLE "Chess"
#define WND_WIDTH 800
#define WND_HEIGHT 600
#define WND_X SDL_WINDOWPOS_CENTERED
#define WND_Y SDL_WINDOWPOS_CENTERED
#define WND_FLAGS SDL_WINDOW_SHOWN

#define REN_DRIVER -1
#define REN_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

#define BOARD_WIDTH 18
#define BOARD_HEIGHT 18

// game status
#define STATUS_NOT_INIT -1
#define STATUS_ERROR -2
#define STATUS_UNKNOWN -3
#define STATUS_NORMAL 0
#define STATUS_BLACK_WON 1
#define STATUS_WHITE_WON 2

// chess
#define CHESS_UNKNOWN 0
#define CHESS_BLACK 1
#define CHESS_WHITE 2

// SDL2
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;

// game data
bool board[BOARD_WIDTH][BOARD_HEIGHT];
static int status = STATUS_NOT_INIT;
static int chessMode = CHESS_UNKNOWN;

// functions
extern "C" {
    // initialize the game.
    // @param wndTitle: the title of game window.
    // @param wndWidth: the width of game window.
    // @param wndHeight: the height of game window.
    // @param wndFlags: the flags that SDL2 window takes.
    // @ret: a int, indicates whether the function succeeded.
    int GameInit(const char *wndTitle  = WND_TITLE,
                 int         wndWidth  = WND_WIDTH,
                 int         wndHeight = WND_HEIGHT,
                 int         wndFlags  = WND_FLAGS
                );

    // exit the game.
    void GameExit(void);

    // update the display according to board.
    void UpdateDisplay(void);

    // get current status of game.
    // @ret: a int. See STATUS_*
    int GetStatus(void);

    // set the status of game.
    // @param value: new value of status.
    void SetStatus(int value);

    // set a new chess.
    // @param mode: the color of chess.
    // @param x: x value of position.
    // @param y: y value of position.
    // @ret: a int, either GAME_SUCCESS or GAME_FAILURE.
    int SetChess(int mode, int x, int y);

    // set current chess mode.
    // @param value: chess mode value.
    void SetChessMode(int value);

    // get the position X on the board according to the mouse
    // position.
    // @ret: X value on the mouse.
    int GetChessX(void);

    // get the position Y on the board according to the mouse
    // position.
    // @ret: Y value.
    int GetChessY(void);

    // get current chess mode.
    // @ret: the current chess mode.
    int GetChessMode(void);
}
#endif  // PROJECT_LIBGAME_GAME_H_
