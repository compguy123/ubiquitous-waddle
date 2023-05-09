// Based on: http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/CHAPTER03/WINDOWS_VERSIONS/example2.cpp
// Modified to isolate the main program and use GLM
#pragma once


#include <glad/glad.h>
//#include <GL/glew.h>
#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#  pragma clang diagnostic ignored "-Wdeprecated-declarations"
#  define glutInitDisplayMode(X) glutInitDisplayMode((X) | GLUT_3_2_CORE_PROFILE)
#  define glutInitContextVersion(X,Y)
#  define glutInitContextProfile(X)
#else // non-Mac OS X operating systems
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__
#include <GLFW/glfw3.h>

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

typedef unsigned int uint;

extern GLuint InitShader(const char* vShaderFile, const char* fShaderFile);

// Implement the following...

extern const char* WINDOW_TITLE;
extern const double FRAME_RATE_MS;
extern const int STARTING_WINDOW_WIDTH;
extern const int STARTING_WINDOW_HEIGHT;

extern void init(void);
extern void update(void);
extern void display(void);
extern void keyboardPressed(unsigned char key, int x, int y);
extern void keyboardReleased(unsigned char key, int x, int y);
extern void mouse(int button, int state, int x, int y);
extern void reshape(int width, int height);


