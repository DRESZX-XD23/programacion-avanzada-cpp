cmake_minimum_required(VERSION 3.20)
project(ColaImpresion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CON_SANITIZERS "interruptor" OFF)

if(CON_SANITIZERS)

 add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
 add_link_options(-fsanitize=address,undefined)
endif()

add_executable(cola main.cpp)
target_compile_options(cola PRIVATE -Wall -Wextra)

find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)

add_executable(Pruebas test_cola.cpp)
target_compile_options(Pruebas PRIVATE -Wall -Wextra)
target_link_libraries(Pruebas PRIVATE GTest::gtest_main)
gtest_discover_tests(Pruebas)