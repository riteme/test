// 人生苦短，快用Python
// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <vector>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#define VECTOR_FLOAT long double
#include "Vector.hpp"

#define FAILURE_ARGUMENTS 1
#define FAILURE_FILEIO 2
#define FAILURE_FORMAT 3
#define FAILURE_SDL_INIT 4
#define FAILURE_SDL_WINDOW_CREATION 5
#define FAILURE_SDL_RENDERER_CREATION 6
#define FAILURE_SDL_TEXTURE_CREATION 7
#define FAILURE_SDL_CONTEXT_CREATION 8
#define FAILURE_GL_GLEW_INIT 9
#define FAILURE_SDL_SURFACE_CREATION 10
#define FAILURE_READ_PIXELS 11
#define FAILURE_SAVE_FILE 12

using std::vector;

static int width, height;
static vector<Vector> standard;
static vector<Vector> user;

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *target;
static SDL_GLContext context;

void initialize(int argc, char *argv[]);
void finalize();

int main(int argc, char *argv[]) {
    initialize(argc, argv);
    atexit(finalize);
    puts("(info) Checker initialized.");

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_ONE, GL_ONE);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);
    for (size_t i = 0; i < standard.size(); i += 3) {
        glVertex2f(standard[i].x, standard[i].y);
        glVertex2f(standard[i + 1].x, standard[i + 1].y);
        glVertex2f(standard[i + 2].x, standard[i + 2].y);
    }
    glEnd();
    glFinish();

    SDL_Surface *surface = NULL;
    surface = SDL_CreateRGBSurface(0, width, height, 32, 0xff000000, 0x00ff0000,
                                   0x0000ff00, 0x000000ff);
    if (!surface) {
        printf("(error) Failed to create surface: %s", SDL_GetError());
        exit(FAILURE_SDL_SURFACE_CREATION);
    }

    void *mPixels;
    int mPitch;
    SDL_LockTexture(target, NULL, &mPixels, &mPitch);
    memcpy(mPixels, surface->pixels, surface->pitch * surface->h);
    SDL_UnlockTexture(target);

    if (SDL_SaveBMP(surface, "output.bmp") < 0) {
        printf("(error) Can't save result into 'output.bmp': %s",
               SDL_GetError());
        exit(FAILURE_SAVE_FILE);
    }

    puts("(info) Saved to 'output.bmp'.");
    puts("(info) Checker exited normally.");
    return 0;
}  // function main

void initialize(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [STANDARD] [USER}\n", argv[0]);
        exit(FAILURE_ARGUMENTS);
    }

    FILE *ans = NULL, *out = NULL;
    ans = fopen(argv[1], "r");
    out = fopen(argv[2], "r");

    if (!ans) {
        printf("(error) Can't open file: %s.\n", argv[1]);
        exit(FAILURE_FILEIO);
    }

    if (!out) {
        printf("(error) Can't open file: %s.\n", argv[2]);
        exit(FAILURE_FILEIO);
    }

    fscanf(ans, "%d%d", &width, &height);
    long double x, y;
    while (fscanf(ans, "%Lf%Lf", &x, &y) != EOF)
        standard.push_back(Vector(x, y));
    while (fscanf(out, "%Lf%Lf", &x, &y) != EOF)
        user.push_back(Vector(x, y));

    if (standard.size() % 3 != 0) {
        printf("(error) Standard input format error: %s", SDL_GetError());
        exit(FAILURE_FORMAT);
    }

    if (user.size() % 3 != 0) {
        printf("(error) User input format error: %s", SDL_GetError());
        exit(FAILURE_FORMAT);
    }

    fclose(ans);
    fclose(out);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("(error) Failed to initialize SDL2: %s", SDL_GetError());
        exit(FAILURE_SDL_INIT);
    }

    window = SDL_CreateWindow(NULL, 0, 0, 1, 1,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
    if (!window) {
        printf("(error) Failed to create window: %s", SDL_GetError());
        exit(FAILURE_SDL_WINDOW_CREATION);
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!renderer) {
        printf("(error) Failed to create renderer: %s", SDL_GetError());
        exit(FAILURE_SDL_RENDERER_CREATION);
    }

    target = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET | SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!target) {
        printf("(error) Failed to create render texture: %s", SDL_GetError());
        exit(FAILURE_SDL_TEXTURE_CREATION);
    }

    SDL_SetRenderTarget(renderer, target);

    context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("(error) Failed to create OpenGL context: %s", SDL_GetError());
        exit(FAILURE_SDL_CONTEXT_CREATION);
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        puts("(error) Can't initialize GLEW.");
        exit(FAILURE_GL_GLEW_INIT);
    }
}

void finalize() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyTexture(target);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
