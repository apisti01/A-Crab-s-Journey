# CMake Version
cmake_minimum_required(VERSION 3.2)
# project name
project(ACrabsJourney)
# Standard C++20
set(CMAKE_CXX_STANDARD 20)

# exe file
add_executable(ACrabsJourney main.cpp)
# add cpp and h files
set(SOURCE_FILES GameCharacter.cpp GameCharacter.h)

# SFML library
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network)
include_directories(D:/SFML/include)
target_link_libraries(ACrabsJourney sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# ???
add_library(core ${SOURCE_FILES})
target_link_libraries(core sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(${PROJECT_NAME} core)

