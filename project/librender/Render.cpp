//
// Copyright 2015 riteme
//

#include "./Render.h"

#include <SDL2/SDL_image.h>

// NOTICE: 和libgame/Game.h中的定义一致
#define GAME_SUCCESS 0
#define GAME_FAILURE -1

using std::string;
using std::unordered_map;

Rectangle axis = {0, 0, 0, 0};
Renderer renderer = nullptr;
Window window = nullptr;
std::unordered_map<std::string, Texture> textureMap;

void BindSdlInstances(Renderer ren, Window wnd) {
    renderer = ren;
    window = wnd;

    // 同步大小
    SyncSize();
}

void SyncSize() {
    if (window != nullptr) {
        SDL_SetWindowSize(window, axis.Width, axis.Height);
    }

    if (renderer != nullptr) {
        SDL_RenderSetLogicalSize(renderer, axis.Width, axis.Height);
    }
}

void ResizeAxis(int width, int height) {
    axis.Width = width;
    axis.Width = height;

    SyncSize();

}
void MoveAxis(int xOffest, int yOffest) {
    axis.X += xOffest;
    axis.Y += yOffest;
}

void MoveToAxisOrigin() {
    axis = {0, 0, 0, 0};
}

void MoveToAxisCenter() {
    // ? : 转换是否必要？
    axis.X = reinterpret_cast<int>(axis.Width / 2);
    axis.Y = reinterpret_cast<int>(axis.Height / 2);
}

int LoadTexture(string &newName, string &filePath) {
    int status = GAME_SUCCESS;

    SDL_Surface *tmpSurface = nullptr;
    SDL_Texture *tmpTexture = nullptr;

    tmpSurface = IMG_Load(filePath.c_str());

    if (tmpSurface == nullptr || renderer == nullptr) {
        status = GAME_FAILURE;
    } else {
        tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);

        if (tmpTexture == nullptr) {
            status = GAME_FAILURE;
        }

        SDL_FreeSurface(tmpSurface);
    }

    if (status != GAME_FAILURE) {
        auto iter = textureMap.find(newName);
        
        // 如果名称已存在，则检查材质是否被创建
        // 若创建，则先销毁之前的材质，
        // 改为新的材质
        if (iter != textureMap.end()) {
            if (iter->second != nullptr) {
                SDL_DestroyTexture(iter->second);
            }

            iter->second = tmpTexture;
        } else {
            textureMap.insert(std::make_pair(newName, tmpTexture));
        }
    }

    return status;
}

Texture GetTexture(string &name) {
    auto iter = textureMap.find(name);

    if (iter != textureMap.end()) {
        return iter->second;
    } else {
        return nullptr;
    }
}

int DestroyTextures() {
    for (auto &e : textureMap) {
        SDL_DestroyTexture(e.second);
    }

    textureMap.clear();

    return GAME_SUCCESS;
}

void ClearDisplay(Color backColor) {
    if (renderer == nullptr) return;

    SDL_SetRenderDrawColor(renderer,
                           backColor.R, backColor.G, backColor.B, backColor.A);
    SDL_RenderClear(renderer);
}

void PresentDisplay() {
#ifndef NDEBUG
    if (renderer == nullptr) return;
#endif

    SDL_RenderPresent(renderer);
}

void _SetDrawColor(Color c) {
#ifndef NDEBUG
    if (renderer == nullptr) return;
#endif

    SDL_SetRenderDrawColor(renderer, c.R, c.G, c.B, c.A);
}

void DrawLine(int x1, int y1, int x2, int y2, Color c) {
#ifndef NDEBUG
    if (renderer == nullptr) return;
#endif

    _SetDrawColor(c);
    SDL_RenderDrawLine(renderer,
                       x1 + axis.X,
                       y1 + axis.Y,
                       x2 + axis.X,
                       y2);
}

void DrawLine(Point point1, Point point2, Color c) {
    DrawLine(point1.X, point1.Y, point2.X, point2.Y, c);
}

void DrawRectangle(int x, int y, int width, int height, Color c) {
#ifndef NDEBUG
    if (renderer == nullptr) return;
#endif

    _SetDrawColor(c);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_RenderDrawRect(renderer, &rect);
}

void DrawRectangle(Rectangle rectangle, Color c) {
    DrawRectangle(rectangle.X,
                  rectangle.Y,
                  rectangle.Width,
                  rectangle.Height,
                  c);
}

void DrawTexture(Texture texture, int x, int y, Color c) {
#ifndef NDEBUG
    if (renderer == nullptr) return;
#endif

    _SetDrawColor(c);

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
