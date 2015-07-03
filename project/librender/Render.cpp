//
// Copyright 2015 riteme
//

#include "./Render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    axis.X = reinterpret_cast<int>(axis.Width / 2);
    axis.Y = reinterpret_cast<int>(axis.Height / 2);
}

Texture LoadTexture(const char *filePath) {
    SDL_Surface *tmpSurface = nullptr;
    tmpSurface = IMG_Load(filePath);

    if (tmpSurface == nullptr) {
        return nullptr;
    }

    if (renderer == nullptr) {
        return nullptr;
    }

    SDL_Texture *tmpTexture = nullptr;
    tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tmpTexture;
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

void SetDrawColor(Color c) {
#ifndef NDEBUG
    if (renderer == nullptr) return;
#endif

    SDL_SetRenderDrawColor(renderer, c.R, c.G, c.B, c.A);
}

void DrawLine(int x1, int y1, int x2, int y2, Color c) {
#ifndef NDEBUG
    if (renderer == nullptr) return;
#endif

    SetDrawColor(c);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void DrawLine(Point point1, Point point2, Color c) {
    DrawLine(point1.X, point1.Y, point2.X, point2.Y, c);
}

void DrawRectangle(int x, int y, int width, int height, Color c) {
#ifndef NDEBUG
    if (renderer == nullptr) return;
#endif

    SetDrawColor(c);

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

    SetDrawColor(c);

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
