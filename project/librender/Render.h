//
// Copyright 2015 riteme
//

#ifndef PROJECT_LIBRENDER_RENDER_H_
#define PROJECT_LIBRENDER_RENDER_H_

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

// NOTICE: 这里只有渲染函数以及一个材质管理器
//         不包括载入和退出

/** 表示一种颜色（RGBA）
 * @member R: 红色分量
 * @member G: 绿色分量
 * @member B: 蓝色分量
 * @member A: Aplha值
 */
struct Color {
    Color(): R(0), G(0), B(0), A(255) {}
    Color(int r, int g, int b, int a)
         : R(r), G(g), B(b) ,A(a) {}

    Color &operator = (const Color &c) {
        this->R = c.R;
        this->G = c.G;
        this->B = c.B;
        this->A = c.A;

        return *this;
    }
    bool operator == (const Color &c) {
        if (c.R == this->R &&
            c.G == this->G &&
            c.B == this->B &&
            c.A == this->A) {
            return true;
        } else {
            return false;
        }
    }

    Uint8 R;
    Uint8 G;
    Uint8 B;
    Uint8 A;
};

/** 表示一个点
 * @member X: X值
 * @member Y: Y值
 */
struct Point {
    Point(): X(0), Y(0) {}
    Point(int x, int y): X(x), Y(y) {}

    Point &operator = (const Point &c) {
        this->X = c.X;
        this->Y = c.Y;

        return *this;
    }
    bool operator == (const Point &c) {
        if (c.X == this->X &&
            c.Y == this->Y) {
            return true;
        } else {
            return false;
        }
    }

    int X;
    int Y;
};

/** 表示一个矩形
 * @member Center: 坐标系原点
 * @member Width: 坐标系宽度
 * @member Height: 坐标系高度
 */
struct Rectangle {
    Rectangle(): Center(0, 0), Width(0), Height(0) {}
    Rectangle(int centerX, int centerY,
         int width, int height)
        : Center(centerX, centerY),
          Width(width),
          Height(height) {}
    Rectangle(Point center, int width, int height)
        : Center(center.X, center.Y),
          Width(width),
          Height(height) {}

    Rectangle &operator = (const Rectangle &c) {
        this->Center = c.Center;
        this->Width = c.Width;
        this->Height = c.Height;

        return *this;
    }
    bool operator == (const Rectangle &c) {
        if (c.Center.X == this->Center.X &&
            c.Center.Y == this->Center.Y &&
            c.Width == this->Width &&
            c.Height == this->Height) {
            return true;
        } else {
            return false;
        }
    }

    Point Center;
    int &X = Center.X;
    int &Y = Center.Y;
    int Width;
    int Height;
};

typedef SDL_Texture* Texture;
typedef SDL_Renderer* Renderer;
typedef SDL_Window* Window;

// 内部使用
extern Rectangle axis;
extern Renderer renderer;
extern Window window;
extern std::unordered_map<std::string, Texture> textureMap;

/** 绑定渲染器和窗口
 * @param ren: 渲染器，即SDL_Renderer的指针
 * @param wnd: 窗口，即SDL_Window的指针
 */
void BindSdlInstances(Renderer ren, Window wnd);

/** 同步与窗口和渲染器的尺寸
 */
void SyncSize(void);

/** 改变坐标轴大小
 * @param width: 新的宽度
 * @param height: 新的高度
 */
void ResizeAxis(int width, int height);

/** 移动坐标轴的原点
 * @param xOffest: 水平方向的移动量
 * @param yOffest: 竖直方向的移动量
 */
void MoveAxis(int xOffest, int yOffest);

/** 是坐标轴移动到原始状态
 */
void MoveAxisToOrigin(void);

/** 移动坐标轴到正中心
 */
void MoveAxisToCenter(void);

/** 加载材质
 * @param newName: 新材质的名称
 * @param filePath: 材质文件路径
 * @ret: 一个整型，指示操作是否成功
 * @remark: 使用SDL_IMG来加载
 *          如果存在同名的材质，**则会将之前的材质删除**
 *          由于创建材质需要渲染器，所以在调用此函数前**先绑定渲染器**
 */
int LoadTexture(std::string &newName, std::string &filePath);

/** 通过名称获取材质
 * @param name: 材质名称
 * @ret: 返回对应的材质
 */
Texture GetTexture(std::string &name);

/** 销毁所有的材质
 * @ret: 一个整型，指示操作是否成功
 */
int DestroyTextures(void);

/** 清除画面
 */
void ClearDisplay(Color backColor);

/** 展示画面
 */
void PresentDisplay(void);

/** 设置当前绘制颜色
 * @param c: 颜色
 * @remark: 用户不应使用该函数
 */
void _SetDrawColor(Color c);

/** 绘制一条直线
 * @params x1, y1: 第一个点的横纵坐标
 * @params x2, y2: 第二个点的横纵坐标
 */
void DrawLine(int x1, int y1, int x2, int y2, Color c);

/** 绘制一条直线
 * @param point1: 第一个点
 * @param point2: 第二个点
 */
void DrawLine(Point point1, Point point2, Color c);

/** 绘制一个矩形
 * @params x, y: 矩形的左上点的横纵坐标
 * @params w, h: 矩形的宽和高
 */
void DrawRectangle(int x, int y, int width, int height, Color c);

/** 绘制一个矩形
 * @param rect: 一个Rectangle结构
 */
void DrawRectangle(Rectangle rectangle, Color c);

/** 绘制材质
 * @param texture: 目标材质
 * @params x, y: 绘制的位置（左上角）
 */
void DrawTexture(Texture texture, int x, int y, Color c);

#endif  // PROJECT_LIBRENDER_RENDER_H_
