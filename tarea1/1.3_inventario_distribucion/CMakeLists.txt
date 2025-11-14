cmake_minimum_required(VERSION 3.10)
project(SistemaInventario)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(inventario
    src/main.cpp
    src/Almacen.cpp
)
