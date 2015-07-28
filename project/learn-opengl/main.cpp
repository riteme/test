//
// Copyright 2015 riteme
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>

#include "./func.hpp"

using std::string;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window *wnd =
        SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 1280, 800, SDL_WINDOW_OPENGL);
    SDL_GLContext opengl = SDL_GL_CreateContext(wnd);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();  // ignore the first error(1280)...

    // ========== PREPARAIONS ==========

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // prepare vertices.
    GLfloat vertices[] = {
        -0.5f, 0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f, // vertex 0
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f, // vertex 1
        0.5f,  -0.5f, 1.0f, 1.0f, 1.0f,  1.0f,  1.0f, // vertex 3
        0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f  // vertex 4
    };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // prepare indices
    GLuint ele[] = {0, 1, 2, 2, 3, 0};
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ele), ele, GL_STATIC_DRAW);

    // compile shaders.
    string vertexSource, fragmentSource;
    vertexSource = ReadAllLinesFromFile("vertex.glsl");
    fragmentSource = ReadAllLinesFromFile("fragment.glsl");

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertexSource_cstr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSource_cstr, NULL);

    std::cout << vertexSource << std::endl;
    CompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragmentSource_cstr = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource_cstr, NULL);

    std::cout << fragmentSource << std::endl;
    CompileShader(fragmentShader);

    // make programs.
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    // use it
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    SetAttr(shaderProgram, "pos", 2, 7, 0);
    SetAttr(shaderProgram, "color", 3, 7, 2);
    SetAttr(shaderProgram, "texcoord", 2, 7, 5);

    /* GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor"); */
    /* glUniform3f(uniColor, 1.0f, 0.0f, 0.0f); */

    // texture
    GLuint textures[2];
    LoadTexture("./google.png", textures[0], true, GL_TEXTURE0);
    auto uniGoogle = glGetUniformLocation(shaderProgram, "texGoogle");
    glUniform1i(uniGoogle, 0);
    LoadTexture("./baidu.jpg", textures[1], false, GL_TEXTURE1);
    auto uniBaidu = glGetUniformLocation(shaderProgram, "texBaidu");
    glUniform1i(uniBaidu, 1);

    auto uniTime = glGetUniformLocation(shaderProgram, "time");
    auto time = 0.0f;
    auto tStart = std::chrono::high_resolution_clock::now();

    constexpr float FPS_TIME_SPAN = 5.0f;
    unsigned fpsCount = 0;
    float timeSpan = 0.0f;

    glUniform1f(uniTime, time);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf(">> Error...   %d\n", error);
        return -1;
    }
    // ========== END ==========

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

        // ========== RENDERING ==========
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* glDrawArrays(GL_TRIANGLES, 0, 3); */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        auto tNow = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::duration<float>>(
                   tNow - tStart).count();
        glUniform1f(uniTime, time);

        SDL_GL_SwapWindow(wnd);

        fpsCount += 1;
        if (time - timeSpan > FPS_TIME_SPAN) {
            auto fps = fpsCount / FPS_TIME_SPAN;
            printf(">  FPS = %f\n", fps);
            fpsCount = 0;
            timeSpan = time;
        }

        SDL_Delay(1);
    }

    glDeleteTextures(2, textures);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    SDL_GL_DeleteContext(opengl);
    SDL_DestroyWindow(wnd);
    SDL_Quit();
}
