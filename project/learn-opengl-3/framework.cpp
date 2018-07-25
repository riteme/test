#include "framework.hpp"

#include <fstream>
#include <sstream>

using namespace std;
using namespace ri;

// FormatConfig logConfig;
DefaultFormatter logFormatter;
DefaultWriter logWriter;
Logger logger;

SDL_Window *window;
SDL_GLContext context;

bool flag = true;

void initialize() {
    // logConfig.SetThreadName("Main Thread");
    logFormatter.SetCurrentThreadName("Main Thread");
    logger.AttachFormatter(&logFormatter);
    logger.AttachWriter(&logWriter);

    logger.SetLevel(LogType::Debug);

    logger.Info("OpenGL application started.");
    logger.Info("Initializing...");

    // Load SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logger.Fatal("Cannot init SDL!");

        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG, SDL_TRUE);

    window =
        SDL_CreateWindow("OpenGL Application", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        logger.Fatal("Cannot create SDL window!");

        exit(-1);
    }

    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        logger.Fatal("Cannot create OpenGL context!");

        exit(-1);
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        logger.Fatal("Cannot init glew!");

        exit(-1);
    }

    glViewport(0, 0, 800, 600);

    atexit(cleanup);
}

void cleanup() {
    logger.Info("Cleaning up...");

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    logger.Info("Application exited.");
}

void do_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: flag = false; break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    flag = false;
                }
                break;
        }  // switch to event.type
    }      // while
}

GLuint load_shader(GLenum shaderType, const std::string &path) {
    logger.Info("Loading shader file: {} ...", path);
    ifstream file(path);

    if (!file.is_open()) {
        logger.Error("Failed to load file: {}", path);

        return 0;
    }

    ostringstream buffer;
    while (file.good()) {
        string tmp;
        getline(file, tmp);
        buffer << tmp << "\n";
    }  // while
    const GLchar *source = buffer.str().data();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        logger.Error("Failed to compile shader file: {}", path);

        GLint infoLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

        GLchar info[infoLength];
        glGetShaderInfoLog(shader, infoLength, nullptr, info);

        logger.Debug("OpenGL Info Log: \n{}", string(info));

        return 0;
    }

    return shader;
}

GLuint make_program(GLuint vertexShader, GLuint fragmentShader) {
    logger.Info("Linking shader program...");

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        logger.Error("Failed to create shader program!");

        GLint infoLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);

        GLchar info[infoLength];
        glGetProgramInfoLog(program, infoLength, nullptr, info);

        logger.Debug("OpenGL Info Log: \n{}", string(info));

        return 0;
    }

    return program;
}
