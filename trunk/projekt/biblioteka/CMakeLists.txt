cmake_minimum_required(VERSION 3.4)
project(Biblioteka)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/funkcje.cpp

add_library(Biblioteka ${SOURCE_FILES})

#dolacz katalog z plikami naglowkowymi include z projektu biblioteka do sciezek
target_include_directories(Biblioteka PUBLIC include)
