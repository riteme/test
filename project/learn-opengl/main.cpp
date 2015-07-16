#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
/* #include <SDL2/SDL_opengl.h> */
#include <GL/glew.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using std::string;
using std::ifstream;

string ReadAllLinesFromFile(const string &filePath) {
    ifstream f(filePath);

    string data;

    if (!f.is_open()) {
        printf("Cannot open file! %s\n", filePath.c_str());
    } else {
        string buf;
        while (f) {
            std::getline(f, buf);
            data += buf;
            data += '\n';
        }
    }

    return data;
}

bool CompileShader(GLuint shader) {
    glCompileShader(shader);

    char logBuf[1024];
    glGetShaderInfoLog(shader, 1024, NULL, logBuf);
    printf("%s\n", logBuf);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    return status == GL_TRUE ? true : false;
}

void SetAttr(GLuint prog, const char *name, int len, int step, int offest) {
    GLint attrPos = glGetAttribLocation(prog, name);
    glEnableVertexAttribArray(attrPos);
    glVertexAttribPointer(attrPos, len, GL_FLOAT, GL_FALSE,
                          step * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(offest * sizeof(GLfloat)));
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

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
        -0.5f, 0.5f,  1.0f, 1.0f,
        1.0f,  0.0f,  0.0f,  // vertex 0
        -0.5f, -0.5f, 1.0f, 1.0f,
        1.0f,  0.0f,  1.0f,  // vertex 1
        0.5f,  -0.5f, 1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  // vertex 3
        0.5f,  0.5f,  1.0f, 1.0f,
        1.0f,  1.0f,  0.0f  // vertex 4
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

    if (!CompileShader(vertexShader)) {
        printf("Cannot compile vertex shader.\n");
        return -1;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragmentSource_cstr = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource_cstr, NULL);

    std::cout << fragmentSource << std::endl;

    if (!CompileShader(fragmentShader)) {
        printf("Cannot compile fragment shader.\n");
        return -1;
    }

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
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    SDL_Surface *surface = nullptr;
    surface = IMG_Load("./google.png");
    if (surface == nullptr) {
        printf("Cannot load texture.\n");
        return -1;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);
    surface = nullptr;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /* glGenerateMipmap(GL_TEXTURE_2D); */

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error...   %d\n", error);
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

        SDL_GL_SwapWindow(wnd);

        SDL_Delay(1);
    }

    glDeleteTextures(1, &tex);
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
