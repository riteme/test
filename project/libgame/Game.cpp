//
// Copyright 2015 riteme
//

#include "./Game.h"

#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

extern "C" {

    int GameInit(const char *wndTitle,
                 int wndWidth,
                 int wndHeight,
                 int wndFlags
                ) {
        if (SDL_Init(SDL_INIT_VIDEO) != GAME_SUCCESS) {
            cerr << "Cannot initialize SDL2!"
                 << endl
                 << "SDL2 information: " << SDL_GetError()
                 << endl;

            SetStatus(Status::Error);
            return GAME_FAILURE;
        }

        // 加载窗口
        window = SDL_CreateWindow(wndTitle,
                                  WND_X, WND_Y,
                                  wndWidth, wndHeight,
                                  wndFlags);
        if (window == nullptr) {  // 若未成功创建， 则返回NULL
            cerr << "Cannot create SDL2 window!"
                 << endl
                 << "SDL2 information: " << SDL_GetError()
                 << endl;

            SetStatus(Status::Error);
            return GAME_FAILURE;
        }

        // 加载渲染器
        renderer = SDL_CreateRenderer(window,
                                      REN_DRIVER, REN_FLAGS);
        if (renderer == nullptr) {  // 同上
            cerr << "Cannot create SDL2 renderer!"
                 << endl
                 << "SDL2 information: " << SDL_GetError()
                 << endl;

            SetStatus(Status::Error);
            return GAME_FAILURE;
        }

        // TODO(riteme): Textures

        // ... 确认数组中每个值均为CHESS_UNKNOWN
        for (auto &x : board) {
            for (auto &y : x) {
                y = Chess::Unknown;
            }
        }

        // 设置当前状态
        SetStatus(Status::Normal);

        return GAME_SUCCESS;
    }

    void GameExit() {
        // 未加载前不应退出
        if (GetStatus() == Status::Error) {
            cerr << "Game is not initialized!"
                 << endl;
            return;
        }
        // TODO(riteme): 首先释放材质

        // 释放渲染器和窗口
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        // 退出SDL2
        SDL_Quit();

        // 设置状态
        SetStatus(Status::NotInit);
    }

    void UpdateDisplay() {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderClear(renderer);
    }
}
