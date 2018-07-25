#ifndef LEARNOPENGL_FRAMEWORK_HPP_
#define LEARNOPENGL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <rilog/Logging.hpp>

extern ri::FormatConfig logConfig;
extern ri::DefaultFormatter logFormatter;
extern ri::DefaultWriter logWriter;
extern ri::Logger logger;

extern SDL_Window *window;
extern SDL_GLContext context;

extern bool flag;

void initialize();
void cleanup();
void do_events();

GLuint load_shader(GLenum shaderType, const std::string &path);
GLuint make_program(GLuint vertexShader, GLuint fragmentShader);

#endif  // LEARNOPENGL_FRAMEWORK_HPP_
