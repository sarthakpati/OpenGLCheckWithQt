cmake_minimum_required(VERSION 3.8.2)

project( OpenGLCheckWithQt VERSION 1.0.0 )
SET( PROJECT_VERSION_MAJOR 1 )
SET( PROJECT_VERSION_MINOR 0 )
SET( PROJECT_VERSION_PATCH 0 )

# Find includes in the build directories

# Turn on automatic invocation of the MOC, UIC & RCC
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

# There may be a way to tell up front if Qt5 is going to be found, but I haven't found
# a foolproof way to do it yet, so settle for the default error message for now.
#if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
#            "environment variable to the install prefix of Qt 5, either on the command line as "
#            "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
#endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
  # set(CMAKE_WIN32_EXECUTABLE ON)
endif()

SET( QT_VERSION "5.12.1" CACHE STRING "Superbuild Qt version to build CaPTk against" FORCE )

IF( EXISTS ${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/lib/cmake/Qt5/Qt5Config.cmake )

  IF (APPLE) # THIS QT FOLDER STRUCTURE WAS NOT REQUIRED FOR 5.11.2 
    SET( ENV{PATH} "${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/clang_64/lib/cmake/Qt5/:${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/clang_64/bin:$ENV{PATH}" CACHE PATH "" FORCE)
    SET( ENV{CMAKE_PREFIX_PATH} "${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/clang_64/lib/cmake/Qt5/:${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/clang_64/bin:$ENV{CMAKE_PREFIX_PATH}" CACHE PATH "" FORCE )
    SET( ENV{CMAKE_PROGRAM_PATH} "${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/clang_64/lib/cmake/Qt5/:${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/clang_64/bin:$ENV{CMAKE_PROGRAM_PATH}" CACHE PATH "" FORCE )
  ELSE()
    SET( ENV{CMAKE_PREFIX_PATH} "${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/lib/cmake/Qt5/:${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/bin:$ENV{CMAKE_PREFIX_PATH}" CACHE PATH "" FORCE )
    SET( ENV{LD_LIBRARY_PATH} "${QT_EXTRACTED_DIR}/${QT_VERSION}/lib/:$ENV{LD_LIBRARY_PATH}" CACHE PATH "" FORCE )
    SET( ENV{CMAKE_PROGRAM_PATH} "${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/lib/cmake/Qt5/:${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/bin:$ENV{CMAKE_PROGRAM_PATH}" CACHE PATH "" FORCE )
    SET( ENV{PATH} "${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/lib/cmake/Qt5/:${PROJECT_BINARY_DIR}/qt/${QT_VERSION}/bin:$ENV{PATH}" CACHE PATH "" FORCE)
  ENDIF()
  
ELSE()
  INCLUDE( cmake_modules/External-Qt.cmake )
ENDIF()

# Find the QtWidgets library
FIND_PACKAGE( Qt5Core 5.12.1 )

# Tell CMake to create the helloworld executable
add_executable(OpenGLCheckWithQt src/main.cxx )

# Add the Qt5 Widgets for linking
target_link_libraries(OpenGLCheckWithQt Qt5::Widgets Qt5::Core Qt5::Gui)

IF( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )

  IF( WIN32 )
    SET( CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install CACHE PATH "Changed the default install path" FORCE  )
  ELSEIF( APPLE )
    # do nothing
  ELSE()
    SET( CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install/appdir/usr CACHE PATH "Changed the default install path" FORCE  )
  ENDIF()
  
ENDIF( )