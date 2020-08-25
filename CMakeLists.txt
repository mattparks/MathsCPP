cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
project(MathsCPP VERSION 0.1.0 LANGUAGES CXX)

include(CXXModules.cmake)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_module_executable(MathsCPP Logger.cpp Vector.cpp Matrix.cpp Quaternion.cpp Colour.cpp Rectangle.cpp Duration.cpp Maths.cpp main.cpp)
target_include_directories(MathsCPP PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_compile_features(MathsCPP PUBLIC cxx_std_20)
target_compile_definitions(MathsCPP PUBLIC _CRT_SECURE_NO_WARNINGS)
