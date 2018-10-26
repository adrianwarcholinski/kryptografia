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
        src/TekstJawny.cpp
        src/Macierze.cpp include/Macierze.h src/SBox.cpp include/SBox.h)
#wlacz wskazane pliki do programu wykonywalnego Program
add_executable(Program ${SOURCE_FILES})

#Dolacz POBILibrary
#target_link_libraries(Program Biblioteka)

#dalacz pliki naglowkowe include projektu glownego
target_include_directories(Program PUBLIC include)


enable_testing()

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_CLIENT_FILES
        test/master.cpp
        test/tekstJawnyTest.cpp)

add_executable (testKrypto ${SOURCE_TEST_CLIENT_FILES})

#dołącz bibliotekę z testowanymi klasami do programu testów
target_link_libraries (testKrypto
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(testKrypto testAES
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

