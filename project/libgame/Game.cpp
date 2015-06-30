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

            SetStatus(STATUS_ERROR);
            return GAME_FAILURE;
        }

        // initialize the window.
        window = SDL_CreateWindow(wndTitle,
                                  WND_X, WND_Y,
                                  wndWidth, wndHeight,
                                  wndFlags);
        if (window == nullptr) {  // if window is not created.
            cerr << "Cannot create SDL2 window!"
                 << endl
                 << "SDL2 information: " << SDL_GetError()
                 << endl;
            
            SetStatus(STATUS_ERROR);
            return GAME_FAILURE;
        }

        // initialize the renderer.
        renderer = SDL_CreateRenderer(window,
                                      REN_DRIVER, REN_FLAGS);
        if (renderer == nullptr) {  // the same as above.
            cerr << "Cannot create SDL2 renderer!"
                 << endl
                 << "SDL2 information: " << SDL_GetError()
                 << endl;

            SetStatus(STATUS_ERROR);
            return GAME_FAILURE;
        }

        // TODO Textures

        // ... make sure all the data are false.
        for (auto &x : board) {
            for (auto &y : x) {
                y = false;
            }
        }

        // set current status.
        SetStatus(STATUS_NORMAL);

        // all done!
        return GAME_SUCCESS;
    }

    void GameExit() {
        // it's not allowed to exit before initializaion.
        if (GetStatus() == STATUS_NOT_INIT) {
            cerr << "Game is not initialized!"
                 << endl;
            return;
        }
        // TODO first free textures.
        
        // free renderer & window.
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        // quit SDL2.
        SDL_Quit();

        // set status.
        SetStatus(STATUS_NOT_INIT);
    }
}
