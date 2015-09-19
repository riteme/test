#include <cassert>

#include <chrono>
#include <string>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

constexpr char VERTEX_SHADER_FILE[] = "./vertex.vsh";
constexpr char FRAGMENT_SHADER_FILE[] = "./fragment.fsh";
constexpr char AXIS_VERTEX_SHADER_FILE[] = "./axis.vsh";
constexpr char AXIS_FRAGMENT_SHADER_FILE[] = "./axis.fsh";
constexpr char TEXTURE_FILE_1[] = "./box.jpg";

/**
 * 从指定的文件中读取渲染器
 *
 * 该函数分为两步，首先从文件中读取源码
 * 然后将读取的源码交给OpenGL
 *
 * @param shader 指定目标渲染器
 * @param path   指定渲染器源码的位置
 *
 * @remark：
 * 该函数不会对渲染器进行编译，编译请使用glCompileShader
 * 中途有一个检查文件是否被打开的assert，可能导致程序退出
 */
void ReadShaderFile(GLuint shader, const std::string &path);

/**
 * 这是主函数，没啥好讲的
 *
 * @return 返回程序的最终状态
 */
int main() {
    // 载入SDL2
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);

    // 设置OpenGL属性
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 创建窗口和OpenGL上下文
    SDL_Window *wnd = nullptr;
    SDL_GLContext context = nullptr;

    wnd = SDL_CreateWindow("OpenGL 3.3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(wnd);

    assert(wnd != nullptr);
    assert(context != nullptr);

    // 载入GLEW
    glewExperimental = GL_TRUE;
    assert(glewInit() == GLEW_OK);
    glGetError();  // GLEW一开始会设置一个没用的设置,忽略即可

    GLint status;

    // 加载顶点渲染器
    GLuint boxVertexShader;
    boxVertexShader = glCreateShader(GL_VERTEX_SHADER);
    ReadShaderFile(boxVertexShader, VERTEX_SHADER_FILE);
    glCompileShader(boxVertexShader);
    glGetShaderiv(boxVertexShader, GL_COMPILE_STATUS, &status);
    assert(status == true);

    // 加载片段渲染器
    GLuint boxFragmentShader;
    boxFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    ReadShaderFile(boxFragmentShader, FRAGMENT_SHADER_FILE);
    glCompileShader(boxFragmentShader);
    glGetShaderiv(boxFragmentShader, GL_COMPILE_STATUS, &status);
    assert(status == true);

    // 加载坐标轴的渲染器
    GLuint axisVertexShader, axisFragmentShader;
    axisVertexShader = glCreateShader(GL_VERTEX_SHADER);
    axisFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    ReadShaderFile(axisVertexShader, AXIS_VERTEX_SHADER_FILE);
    ReadShaderFile(axisFragmentShader, AXIS_FRAGMENT_SHADER_FILE);
    glCompileShader(axisVertexShader);
    glCompileShader(axisFragmentShader);
    glGetShaderiv(axisVertexShader, GL_COMPILE_STATUS, &status);
    assert(status == true);
    glGetShaderiv(axisFragmentShader, GL_COMPILE_STATUS, &status);
    assert(status == true);

    // 制作渲染程序
    GLuint boxShaderProgram;
    boxShaderProgram = glCreateProgram();
    glAttachShader(boxShaderProgram, boxVertexShader);
    glAttachShader(boxShaderProgram, boxFragmentShader);
    glLinkProgram(boxShaderProgram);
    glGetProgramiv(boxShaderProgram, GL_LINK_STATUS, &status);
    assert(status == true);

    // 制作坐标轴渲染程序
    GLuint axisShaderProgram;
    axisShaderProgram = glCreateProgram();
    glAttachShader(axisShaderProgram, axisVertexShader);
    glAttachShader(axisShaderProgram, axisFragmentShader);
    glLinkProgram(axisShaderProgram);
    glGetProgramiv(axisShaderProgram, GL_LINK_STATUS, &status);
    assert(status == true);

    // 删除渲染器
    // 连接后不再需要
    glDeleteShader(boxVertexShader);
    glDeleteShader(boxFragmentShader);
    glDeleteShader(axisVertexShader);
    glDeleteShader(axisFragmentShader);

    // 加载材质
    SDL_Surface *textureData1 = nullptr;
    textureData1 = IMG_Load(TEXTURE_FILE_1);
    assert(textureData1 != nullptr);

    GLuint textures[1];
    glGenTextures(1, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData1->w, textureData1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData1->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    assert(textures[0] != 0);

    SDL_FreeSurface(textureData1);

    // 设置顶点数据
    GLfloat axisVertices[] = {
        0.0f,    0.0f,    0.0f,    1.0f, 0.0f, 0.0f,  // x start
        1000.0f, 0.0f,    0.0f,    1.0f, 0.0f, 0.0f,  // x end
        0.0f,    0.0f,    0.0f,    0.0f, 1.0f, 0.0f,  // y start
        0.0f,    1000.0f, 0.0f,    0.0f, 1.0f, 0.0f,  // y end
        0.0f,    0.0f,    0.0f,    0.0f, 0.0f, 1.0f,  // z start
        0.0f,    0.0f,    1000.0f, 0.0f, 0.0f, 1.0f   // z end
    };

    GLfloat vertices[] = {
        // x    y      r     g     b     s     t
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // 0
        0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // 1
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // 3
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // 4

        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // 5
        0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // 6
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // 7
        -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // 8

        -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // 9
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // 10
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // 11
        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // 12

        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // 13
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // 14
        0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // 15
        0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // 16

        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // 17
        0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // 18
        0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // 19
        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // 20

        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // 21
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // 22
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // 23
        -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // 24
    };

    // 设置索引数组
    GLuint indices[] = {
        0,  1,  2,  2,  3,  0,   // face 1
        4,  5,  6,  6,  7,  4,   // face 2
        8,  9,  10, 10, 11, 8,   // face 3
        12, 13, 14, 14, 15, 12,  // face 4
        16, 17, 18, 18, 19, 16,  // face 5
        20, 21, 22, 22, 23, 20   // face 6
    };

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;

    projection = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);
    view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::mat4();

    constexpr GLuint AXIS_INDEX = 0;
    constexpr GLuint BOX_INDEX = 1;

    // 生成VAO
    GLuint VAO[2];
    glGenVertexArrays(2, VAO);
    assert(VAO[0] != 0);
    assert(VAO[1] != 0);

    // 生成VBO
    GLuint VBO[2];
    glGenBuffers(2, VBO);
    assert(VBO[0] != 0);
    assert(VBO[1] != 0);

    // 生成EBO
    GLuint EBO;
    glGenBuffers(1, &EBO);
    assert(EBO != 0);

    // 绑定box的相关设置
    glBindVertexArray(VAO[BOX_INDEX]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[BOX_INDEX]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_READ);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glUseProgram(boxShaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, reinterpret_cast<GLvoid *>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // 设置box的uniform
    GLint uniBoxProjection = glGetUniformLocation(boxShaderProgram, "projection");
    GLint uniBoxView = glGetUniformLocation(boxShaderProgram, "view");
    GLint uniBoxModel = glGetUniformLocation(boxShaderProgram, "model");
    assert(uniBoxProjection != -1);
    assert(uniBoxView != -1);
    assert(uniBoxModel != -1);

    glUniformMatrix4fv(uniBoxProjection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(uniBoxView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(uniBoxModel, 1, GL_FALSE, glm::value_ptr(model));

    assert(glGetError() == GL_NO_ERROR);

    // 绑定坐标轴的相关设置
    glBindVertexArray(VAO[AXIS_INDEX]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[AXIS_INDEX]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    glUseProgram(axisShaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // 设置坐标轴的uniform
    GLint uniAxisProjection = glGetUniformLocation(axisShaderProgram, "projection");
    GLint uniAxisView = glGetUniformLocation(axisShaderProgram, "view");
    GLint uniAxisModel = glGetUniformLocation(axisShaderProgram, "model");
    assert(uniAxisProjection != -1);
    assert(uniAxisView != -1);
    assert(uniAxisModel != -1);

    glUniformMatrix4fv(uniAxisProjection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(uniAxisView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(uniAxisModel, 1, GL_FALSE, glm::value_ptr(model));

    assert(glGetError() == GL_NO_ERROR);

    // OpenGL的其他设置
    glEnable(GL_DEPTH_TEST);

    assert(glGetError() == GL_NO_ERROR);

    auto start = chrono::high_resolution_clock::now();
    bool flag = true;  // 指示运行状态
    SDL_Event e;       // SDL2的事件

    GLfloat rotateX = 0.0f;
    GLfloat rotateY = 0.0f;
    GLfloat rotateZ = 0.0f;

    string text;
    string finalText;
    Sint32 textStart;
    Sint32 selLen;

    // 主循环
    while (flag) {
        // 事件处理
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT: flag = false; continue;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_q: rotateX = -1.0f; break;
                        case SDLK_w: rotateX = 1.0f; break;
                        case SDLK_a: rotateY = -1.0f; break;
                        case SDLK_s: rotateY = 1.0f; break;
                        case SDLK_z: rotateZ = -1.0f; break;
                        case SDLK_x: rotateZ = 1.0f; break;

                        case SDLK_ESCAPE: flag = false; continue;
                    }  // switch to e.key.keysym.sym
                    break;
                case SDL_KEYUP:
                    switch (e.key.keysym.sym) {
                        case SDLK_q:
                        case SDLK_w: rotateX = 0.0f; break;
                        case SDLK_a:
                        case SDLK_s: rotateY = 0.0f; break;
                        case SDLK_z:
                        case SDLK_x: rotateZ = 0.0f; break;
                        case SDLK_F1: SDL_StopTextInput(); break;
                        case SDLK_F2:
                            SDL_StartTextInput();
                            SDL_Rect inputRect = { 0, 0, 800, 600 };
                            SDL_SetTextInputRect(&inputRect);
                            break;
                    }  // switch to e.key.keysym.sym
                    break;
                case SDL_TEXTINPUT:
                    /* Add new text onto the end of our text */
                    if (e.key.keysym.sym == SDLK_BACKSPACE) {
                        text.pop_back();
                        break;
                    } else { text += e.text.text; }
                    cout << "text: " << text << endl;
                    break;
                case SDL_TEXTEDITING:
                    finalText = e.edit.text;
                    textStart = e.edit.start;
                    selLen = e.edit.length;
                    cout << "FINAL: " << finalText << endl;
                    break;
            }  // switch to e.type
        }

        // 渲染区
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto end = chrono::high_resolution_clock::now();
        auto passedTime = chrono::duration_cast<chrono::duration<float>>(end - start).count();

        model = glm::mat4();
        if (!(rotateX == 0.0f && rotateY == 0.0f && rotateZ == 0.0f)) {
            model = glm::rotate(model, passedTime * 20.0f, glm::vec3(rotateX, rotateY, rotateZ));
        }

        // glBindBuffer(GL_ARRAY_BUFFER, VBO[BOX_INDEX]);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glUseProgram(boxShaderProgram);
        glBindVertexArray(VAO[BOX_INDEX]);
        glUniformMatrix4fv(uniBoxModel, 1, GL_FALSE, glm::value_ptr(model));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // glBindBuffer(GL_ARRAY_BUFFER, VBO[AXIS_INDEX]);
        glUseProgram(axisShaderProgram);
        glBindVertexArray(VAO[AXIS_INDEX]);
        glUniformMatrix4fv(uniAxisModel, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_LINES, 0, 6);

        // 提交
        SDL_GL_SwapWindow(wnd);
    }  // while

    // 删除渲染程序
    glDeleteProgram(boxShaderProgram);
    glDeleteProgram(axisShaderProgram);

    // 删除EBO
    glDeleteBuffers(1, &EBO);

    // 删除VBO
    glDeleteBuffers(2, VBO);

    // 删除VAO
    glDeleteVertexArrays(2, VAO);

    // 销毁窗口和OpenGL上下文
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(wnd);

    // 退出SDL2
    SDL_Quit();

    return 0;
}  // function main

void ReadShaderFile(GLuint shader, const std::string &path) {
    std::ifstream fileReader(path);

    assert(fileReader.is_open());

    std::string lineBuffer, fileBuffer;
    while (std::getline(fileReader, lineBuffer)) {
        fileBuffer += lineBuffer;
        fileBuffer += '\n';
    }  //  while

    const GLchar *source = fileBuffer.data();
    glShaderSource(shader, 1, &source, nullptr);
}
