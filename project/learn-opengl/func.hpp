#ifndef FUNC_HPP
#define FUNC_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <cstdio>
using std::string;
using std::ifstream;

string ReadAllLinesFromFile(const string &filePath);
void CompileShader(GLuint shader);
void SetAttr(GLuint prog, const char *name, unsigned len, unsigned step,
             unsigned offest);
void LoadTexture(const string &file, GLuint tex, bool isRGBA = true,
                 GLenum texUnit = GL_TEXTURE0);

string ReadAllLinesFromFile(const string &filePath) {
    ifstream f(filePath);

    string data;

    if (!f.is_open()) {
        printf(">> Cannot open file! %s\n", filePath.c_str());
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

void CompileShader(GLuint shader) {
    glCompileShader(shader);

    GLint logSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    char *log = new char[static_cast<unsigned>(logSize)];
    glGetShaderInfoLog(shader, logSize, NULL, log);
    printf("%s\n", log);
    delete[] log;

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        printf(">> Cannot compile shader!   %d\n", status);
    } else {
        printf(">  Shader compiled successfully!\n");
    }
}

void SetAttr(GLuint prog, const char *name, unsigned len, unsigned step,
             unsigned offest) {
    GLint attrPos = glGetAttribLocation(prog, name);
    glEnableVertexAttribArray(attrPos);
    glVertexAttribPointer(attrPos, len, GL_FLOAT, GL_FALSE,
                          step * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(offest * sizeof(GLfloat)));
}

void LoadTexture(const string &file, GLuint tex, bool isRGBA, GLenum texUnit) {
    glGenTextures(1, &tex);
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, tex);

    SDL_Surface *surface = nullptr;
    surface = IMG_Load(file.c_str());
    if (surface == nullptr) {
        printf(">> Cannot load texture from file '%s'.\n", file.c_str());
        return;
    }
    GLint imgFmt = GL_RGBA;
    if (!isRGBA) {
        imgFmt = GL_RGB;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, imgFmt, surface->w, surface->h, 0,
                 static_cast<GLenum>(imgFmt), GL_UNSIGNED_BYTE,
                 surface->pixels);
    SDL_FreeSurface(surface);
    surface = nullptr;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /* glGenerateMipmap(GL_TEXTURE_2D); */
}

#endif  // FUNC_HPP
