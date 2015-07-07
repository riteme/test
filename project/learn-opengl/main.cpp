#include <SDL2/SDL.h>
#include <GL/glew.h>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_Window *wnd =
        SDL_CreateWindow("OpenGl", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 1280, 800, SDL_WINDOW_OPENGL);
    SDL_GLContext opengl = SDL_GL_CreateContext(wnd);

    glewExperimental = GL_TRUE;
    glewInit();

    float vertices[] = {0.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f};
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    SDL_Event e;
    bool flag = true;
    while (flag) {
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT: flag = false; continue;
                case SDL_KEYUP:
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE: flag = false; continue;
                    }
                    break;
            }
        }

        SDL_GL_SwapWindow(wnd);

        SDL_Delay(1);
    }

    SDL_GL_DeleteContext(opengl);
    SDL_DestroyWindow(wnd);
    SDL_Quit();
}
