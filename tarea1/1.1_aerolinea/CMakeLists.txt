cmake_minimum_required(VERSION 3.10)
project(AerolineaSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(aerolinea ${SOURCES})

# Opcionales: warnings
if (MSVC)
  target_compile_options(aerolinea PRIVATE /W4 /permissive-)
else()
  target_compile_options(aerolinea PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()
