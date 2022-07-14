# CMake Version
cmake_minimum_required(VERSION 3.2)
# project name
project(ACrabsJourney)
# Standard C++20
set(CMAKE_CXX_STANDARD 20)

#add the directory for the unit testing
add_subdirectory(test)

# add cpp and h files
set(SOURCE_FILES GameCharacter.cpp GameCharacter.h Item.cpp Item.h Weapon.h Weapon.cpp Wearable.cpp Wearable.h Consumable.cpp Consumable.h MeleeWeapon.cpp MeleeWeapon.h RangedWeapon.cpp RangedWeapon.h Bullet.cpp Bullet.h Enemy.cpp Enemy.h
        Player.cpp Player.h AnimatedSprite.cpp AnimatedSprite.h Obstacle.cpp Obstacle.h StaticRangedEnemy.cpp StaticRangedEnemy.h Room.h Room.cpp FloorMap.h FloorMap.cpp)
# executable file
add_executable(ACrabsJourney main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(ACrabsJourney core)

# SFML library
IF (WIN32)
    # set stuff for windows
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR D:/SFML/lib/cmake/SFML)
    find_package(SFML COMPONENTS system window graphics audio)
    include_directories(D:/SFML/include)
ELSE()
    # set stuff for other systems
    set(SFML_STATIC_LIBRARIES, TRUE)
    find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
ENDIF()

target_link_libraries(ACrabsJourney sfml-system sfml-window sfml-graphics sfml-audio)
