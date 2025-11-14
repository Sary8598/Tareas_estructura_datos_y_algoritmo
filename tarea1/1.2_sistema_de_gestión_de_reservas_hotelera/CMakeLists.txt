cmake_minimum_required(VERSION 3.10)
project(hotel_reservas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Cliente.cpp
    src/Habitacion.cpp
    src/Hotel.cpp
)

add_executable(hotel_reservas ${SOURCES})