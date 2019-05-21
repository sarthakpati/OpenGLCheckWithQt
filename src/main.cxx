#include "qapplication.h"
#include "qoffscreensurface.h"
#include "qopenglcontext.h"
#include "qdebug.h"
#include "qopenglfunctions.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QOffscreenSurface surf;
  surf.create();

  QOpenGLContext ctx;
  ctx.create();
  ctx.makeCurrent(&surf);

  qDebug() << (const char*)ctx.functions()->glGetString(GL_VERSION);
  qDebug() << (const char*)ctx.functions()->glGetString(GL_EXTENSIONS);

  return 0;

}