cmake_minimum_required(VERSION 3.20)
project(lab_test)

set(CMAKE_CXX_STANDARD 17)

set(sources
	./source/main.cpp
	)

add_executable(mainApp ${sources})
target_compile_options(mainApp PRIVATE -Wall -pedantic -std=c++17)
target_link_libraries(mainApp)

set(tests
	./tests/tests.cpp
	./tests/tests-main.cpp
	./source/solve.hpp
	)
	
add_subdirectory(Catch2)
add_executable(runTests ${tests})
target_compile_options(runTests PRIVATE -g)
target_link_libraries(runTests PRIVATE Catch2::Catch2)
