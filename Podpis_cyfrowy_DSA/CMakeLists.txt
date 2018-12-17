cmake_minimum_required(VERSION 3.13)
project(Podpis_cyfrowy_DSA)

set(CMAKE_CXX_STANDARD 14)

add_executable(Podpis_cyfrowy_DSA src/main.cpp
                include/DuzyInt.h src/DuzyInt.cpp
                include/Math.h src/Math.cpp
                src/MD5Hash.cpp)