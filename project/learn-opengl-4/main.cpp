// #define NDEBUG

#include <SDL2/SDL.h>
#include <GL/glew.h>

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 600;

static SDL_Window *window;
static SDL_GLContext context;

void initialize();
void finalize();
void do_event(SDL_Event &event);
void update();
void render();

int main() {
    initialize();
    atexit(finalize);

    bool exited = false;
    SDL_Event event;
    while (!exited) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exited = true;
                break;
            } else
                do_event(event);
        }  // while

        update();

        glClear(GL_COLOR_BUFFER_BIT);
        render();
        glFlush();
        SDL_GL_SwapWindow(window);
    }  // while

    return 0;
}  // function main

void initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight,
                              SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow() failed: %s\n", SDL_GetError());
        exit(-1);
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
        fprintf(stderr, "SDL_GL_CreateContext() failed: %s\n", SDL_GetError());
        exit(-1);
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "glewInit() failed.\n");
        exit(-1);
    }

    glViewport(0, 0, WindowWidth, WindowHeight);
    glClearColor(0.2, 0.3, 0.3, 1.0);
}

void finalize() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void do_event(SDL_Event &event) {}

void update() {}

void render() {}
