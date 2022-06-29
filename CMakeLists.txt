cmake_minimum_required(VERSION 3.22)
project(ACrabsJourney)

set(CMAKE_CXX_STANDARD 20)

set(SFML_STATIC_LIBRARIES, TRUE)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set(SOURCE_FILES GameCharacter.cpp GameCharacter.h)

add_executable(ACrabsJourney main.cpp)

add_library(core ${SOURCE_FILES})
target_link_libraries(core sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(${PROJECT_NAME} core)

