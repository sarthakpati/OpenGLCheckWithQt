#include <iostream>

#include "CheckOpenGLVersion.h"

#include "qapplication.h"

#ifdef _WIN32
// ensures no console pops up when launching the program
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  int argc = __argc;
  char **argv = __argv;
#else
int main(int argc, char** argv)
{
#endif

  QApplication app(argc, argv);

  app.processEvents();

#if WIN32
  CheckOpenGLVersion checker(hInstance);
#else
  CheckOpenGLVersion checker;
#endif

  if (!checker.hasVersion_3_2())
  {
    std::string msg = "A working 3.2 version of OpenGL was not found in your hardware/software combination; consequently, CaPTk's GUI will not work; all CLIs will work as expected.\n\n";
    msg += "\tOpenGL Version : " + checker.version + "\n";
    msg += "\tOpenGL Renderer: " + checker.renderer + "\n";
    msg += "\tOpenGL Vendor  : " + checker.vendor;
    std::cerr << msg << "\n";
    return EXIT_FAILURE;
  }
  else
  {
    std::cout << "Compatible OpenGL was found.\n";
  }
  
  return app.exec();

}