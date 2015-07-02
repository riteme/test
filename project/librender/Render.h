//
// Copyright 2015 riteme
//

#ifndef PROJECT_LIBRENDER_RENDER_H_
#define PROJECT_LIBRENDER_RENDER_H_

#include <SDL2/SDL.h>

// NOTICE: 这里只有渲染函数
//         这里只有渲染函数不包括载入和退出

/** 表示一个点
 * @member X: X值
 * @member Y: Y值
 */
struct Point {
    int X = 0;
    int Y = 0;
}

/** 表示一个材质
 * @remark: 就是SDL_Texture
 */
typedef SDL_Texture Texture;

static int axisX = 0, axisY = 0;

/** 移动坐标轴的原点
 * @param xOffest: 水平方向的移动量
 * @param yOffest: 竖直方向的移动量
 */
void MoveAxis(int xOffest, int yOffest);
void MoveToOrigin(void);
void MoveToCenter(void);
Texture *LoadTexture(const char *filePath);
void DrawLine(int pointX, int pointY);
void DrawLine(Point point);
void DrawLines(int cnt, int *pointX, int *pointY);
void DrawLines(int cnt, Point *points);
void DrawTexture(Texture *texture, int x, int y);

#endif
