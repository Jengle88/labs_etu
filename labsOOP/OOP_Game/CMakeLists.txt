cmake_minimum_required(VERSION 3.20)
project(OOP_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP_lab main.cpp UI/Models/Cell.cpp UI/Models/Cell.h Objects/CellObject.cpp Objects/CellObject.h UI/Field.cpp UI/Field.h Tools/Grid.cpp Tools/Grid.h Tools/CellPoint.cpp Tools/CellPoint.h)
