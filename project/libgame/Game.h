//
// Copyright 2015 riteme
//

#ifndef PROJECT_LIBGAME_GAME_H_
#define PROJECT_LIBGAME_GAME_H_

#include <SDL2/SDL.h>

// NOTICE:
// 在C++11中，使用constexpr代替宏

// #define GAME_SUCCESS 0
// #define GAME_FAILURE -1
constexpr int GAME_SUCCESS = 0;
constexpr int GAME_FAILURE = -1;

// 窗口默认值
// #define WND_TITLE "Chess"
// #define WND_WIDTH 800
// #define WND_HEIGHT 600
// #define WND_X SDL_WINDOWPOS_CENTERED
// #define WND_Y SDL_WINDOWPOS_CENTERED
// #define WND_FLAGS SDL_WINDOW_SHOWN
constexpr char WND_TITLE[] = "Chess";
constexpr int WND_WIDTH = 800;
constexpr int WND_HEIGHT = 600;
constexpr int WND_X = SDL_WINDOWPOS_CENTERED;
constexpr int WND_Y = SDL_WINDOWPOS_CENTERED;
constexpr int WND_FLAGS = SDL_WINDOW_SHOWN;

// 渲染器默认值
// #define REN_DRIVER -1
// #define REN_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
constexpr int REN_DRIVER = -1;
constexpr int REN_FLAGS = SDL_RENDERER_ACCELERATED |
                          SDL_RENDERER_PRESENTVSYNC;

// 18x18 = 391
// #define BOARD_WIDTH 18
// #define BOARD_HEIGHT 18
constexpr int BOARD_WIDTH = 18;
constexpr int BOARD_HEIGHT = 18;

// 状态宏定义
// #define STATUS_NOT_INIT -1
// #define STATUS_ERROR -2
// #define STATUS_UNKNOWN -3
// #define STATUS_NORMAL 0
// #define STATUS_BLACK_WON 1
// #define STATUS_WHITE_WON 2

/** 状态枚举
 * @enum NotInit: 表示还未载入
 * @enum Error: 表示当前存在一些错误
 * @enum Unknown: 表示未知的状态
 * @enum Normal: 表示正常进行
 * @enum BlackNow: 表示轮到黑子下
 * $enum WhiteNow: 表示轮到白子下
 * @remark: 除非实在无法确定状态，否则不是使用Unknown
 */
enum class Status {
    NotInit  = -1,
    Error    = -2,
    Unknown  = -3,
    Normal   = 0,
    BlackNow = 1,
    WhiteNow = 2
};

// chess
// #define CHESS_UNKNOWN 0
// #define CHESS_BLACK 1
// #define CHESS_WHITE 2

/** 表示棋子颜色
 * @enum Unknown: 未知
 * @enum Black: 黑子
 * @enum White: 白子
 */
enum class Chess {
    Unknown = 0,
    Black   = 1,
    White   = 2
};

// #define CHESS_WIDTH 50
// #define CHESS_HEIGHT 50
constexpr int CHESS_WIDTH = 50;
constexpr int CHESS_HEIGHT = 50;
constexpr int CHESS_MARGIN = 6;

// 渲染器和窗口声明
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;

// 游戏数据
static Chess board[BOARD_WIDTH][BOARD_HEIGHT];
static Chess chessMode = Chess::Unknown;
static Status status = Status::NotInit;

extern "C" {
    /** 载入游戏
     *  将会载入SDL2、窗口和渲染器
     * @param wndTitle: 窗口标题
     * @param wndWidth: 窗口宽度
     * @param wndHeight: 窗口高度
     * @param wndFlags: 窗口参数
     * @ret: 返回一个整型，指示执行状态
     */
    int GameInit(const char *wndTitle  = WND_TITLE,
                 int         wndWidth  = WND_WIDTH,
                 int         wndHeight = WND_HEIGHT,
                 int         wndFlags  = WND_FLAGS);

    /* 退出游戏 */
    void GameExit(void);

    /* 更新画面 */
    void UpdateDisplay(void);

    /** 获取当前状态
     * @ret: 返回一个Status枚举，即当前的状态
     */
    Status GetStatus(void);

    /** 设置状态
     * @param 状态值
     */
    void SetStatus(Status value);

    /** 设置一步棋
     * @param mode: 棋子的颜色
     * @param x: 棋子的横坐标
     * @param y: 棋子的纵坐标
     * @ret: 返回一个整型，即GAME_SUCCESS或GAME_FAILURE
     */
    int SetChess(int mode, int x, int y);

    /** 设置当前棋色
     * @param value: 棋色
     */
    void SetChessMode(int value);

    /** 获取鼠标在棋盘上的横坐标 
     * @ret: 一个整型，即横坐标
     */
    int GetChessX(void);

    /** 获取鼠标在棋盘上的纵坐标
     * @ret: 一个整型，即纵坐标
     */
    int GetChessY(void);

    /** 返回当前的签字状态
     * @ret: 返回一个Chess枚举
     */
    Chess GetChessMode(void);
}

#endif  // PROJECT_LIBGAME_GAME_H_
