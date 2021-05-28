cmake_minimum_required(VERSION 3.5)

project(BMP_Editor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
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

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(BMP_Editor SHARED
          /main.cpp
          /mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(BMP_Editor
          main.cpp
          mainwindow.cpp
          libs/mainwindow.h
          forms/mainwindow.ui
          createsquareform.cpp
          libs/createsquareform.h
          forms/createsquareform.ui
          bmp_libs/BMP_edit.cpp
          bmp_libs/BMP_edit.h
          bmp_libs/Byte.h
          changergbfilterform.cpp
          libs/changergbfilterform.h
          forms/changergbfilterform.ui
          rotatefragmentform.cpp
          libs/rotatefragmentform.h
          forms/rotatefragmentform.ui
          drawcircleform.cpp
          libs/drawcircleform.h
          forms/drawcircleform.ui
          icon.qrc
          makeframeform.cpp
          libs/makeframeform.h
          forms/makeframeform.ui
  )
endif()

target_link_libraries(BMP_Editor PRIVATE Qt5::Widgets)
