#include "framework.hpp"

#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;
using namespace ri;

static GLfloat vertices[] = { 0.0f, 0.5f,  0.0f,  0.5f, -0.5f,
                              0.0f, -0.5f, -0.5f, 0.0f };
static GLuint VAO;
static GLuint VBO;
static GLuint vertexShader;
static GLuint fragmentShader;
static GLuint program;

void loadGL();
void quitGL();

int main() {
    initialize();
    loadGL();

    while (flag) {
        do_events();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }  // while

    return 0;
}  // function main

void loadGL() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    vertexShader = load_shader(GL_VERTEX_SHADER, "vertex.vert");
    fragmentShader = load_shader(GL_FRAGMENT_SHADER, "fragment.frag");
    program = make_program(vertexShader, fragmentShader);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    atexit(quitGL);
}

void quitGL() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
    glDeleteBuffers(1, &VBO);
}
