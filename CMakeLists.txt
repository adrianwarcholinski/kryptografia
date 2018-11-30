cmake_minimum_required(VERSION 3.4)
#Parametry konfiguracyjne cmake
set(CMAKE_CXX_COMPILER g++)#wymaga by g++ był na ścieżce
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Profil debug i maksymalny poziom debug info g3 oraz format debug info na dwarf-4 (musi być gdb w wersji 7)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")

enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
project(Program)


#ustaw zbior plików zrodlowych projektu
set(SOURCE_FILES
        src/main.cpp
        )
#wlacz wskazane pliki do programu wykonywalnego Program
add_executable(Program ${SOURCE_FILES})

#Dolacz POBILibrary
#target_link_libraries(Program Biblioteka)

#dalacz pliki naglowkowe include projektu glownego
target_include_directories(Program PUBLIC include)



