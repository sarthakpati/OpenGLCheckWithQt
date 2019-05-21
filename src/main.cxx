#include <iostream>

#include "qapplication.h"
#include "qoffscreensurface.h"
#include "qopenglcontext.h"
#include "qdebug.h"
#include "qopenglfunctions.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QOffscreenSurface surf;
  surf.create();

  QOpenGLContext ctx;
  ctx.create();
  ctx.makeCurrent(&surf);
  
  std::string gl_version = reinterpret_cast<const char*>(ctx.functions()->glGetString(GL_VERSION));
  std::string gl_extensions = reinterpret_cast<const char*>(ctx.functions()->glGetString(GL_EXTENSIONS));

  std::cout << "OpenGL Version: " << gl_version << "\n===\n";
  std::cout << "OpenGL Extensions: " << gl_extensions << "\n";
  
  return 0;

}