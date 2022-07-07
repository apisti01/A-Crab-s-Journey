# CMake Version
cmake_minimum_required(VERSION 3.2)
# project name
project(ACrabsJourney)
# Standard C++20
set(CMAKE_CXX_STANDARD 20)

#add the directory for the unit testing
add_subdirectory(test)

# add cpp and h files
set(SOURCE_FILES GameCharacter.cpp GameCharacter.h FloorMap.cpp FloorMap.h Room.cpp Room.h Obstacle.cpp Obstacle.h)
# exe file
add_executable(ACrabsJourney main.cpp)
add_library(core ${SOURCE_FILES})

# SFML library
IF (WIN32)
    # set stuff for windows
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR D:/SFML/lib/cmake/SFML)
    find_package(SFML COMPONENTS system window graphics audio)
    include_directories(D:/SFML/include)
    target_link_libraries(ACrabsJourney sfml-system sfml-window sfml-graphics sfml-audio)
ELSE()
    # set stuff for other systems
    set(SFML_STATIC_LIBRARIES, TRUE)
    find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
    target_link_libraries(ACrabsJourney sfml-system sfml-window sfml-graphics sfml-audio)
ENDIF()

target_link_libraries(ACrabsJourney sfml-system sfml-window sfml-graphics sfml-audio)
