cmake_minimum_required(VERSION 3.20)
project(OOP_Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP_Game main.cpp Objects/CellObject.cpp Objects/CellObject.h Tools/CellPoint.cpp Tools/CellPoint.h Tools/Grid.cpp Tools/Grid.h UI/Models/Field.cpp UI/Models/Field.h UI/Models/Cell.cpp UI/Models/Cell.h Playground/playground.cpp Tools/FieldIterator.cpp Tools/FieldIterator.h)
