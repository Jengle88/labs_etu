cmake_minimum_required(VERSION 3.5)

project(compGraphics LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

if(ANDROID)
  add_library(compGraphics SHARED
          app/main.cpp
          ui/splashWindow/splashwindow.cpp
          ui/splashWindow/splashwindow.h
          ui/splashWindow/splashwindow.ui
  )
else()
  add_executable(compGraphics
          app/main.cpp
          ui/splashWindow/splashwindow.cpp
          ui/splashWindow/splashwindow.h
          ui/splashWindow/splashwindow.ui
          ui/lab1Window/lab1widget.cpp
          ui/lab1Window/lab1widget.h
          ui/lab1Window/lab1widget.ui
          app/App.h
          labs/lab1/Lab1Primitives.cpp
          labs/lab1/Lab1Primitives.h
          ui/openGLWidget/OpenGLWidget.cpp
          ui/openGLWidget/OpenGLWidget.h
          ui/lab2Window/lab2widget.cpp
          ui/lab2Window/lab2widget.h
          ui/lab2Window/lab2widget.ui
          labs/lab2/Lab2Primitives.cpp labs/lab2/Lab2Primitives.h)
endif()

# Qt library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# OpenGL & GLEW library
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(compGraphics PRIVATE Qt5::Widgets Qt5::OpenGL OpenGL::GL GLUT::GLUT)

