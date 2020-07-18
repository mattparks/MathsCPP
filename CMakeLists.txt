cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
project(MathsCPP VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_executable(MathsCPP main.cpp Maths.hpp Logger.hpp Vector.hpp Matrix.hpp Quaternion.hpp Colour.hpp Rectangle.hpp Duration.hpp)
target_include_directories(MathsCPP PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_compile_features(MathsCPP PUBLIC cxx_std_17)
target_compile_definitions(MathsCPP PUBLIC _CRT_SECURE_NO_WARNINGS)
