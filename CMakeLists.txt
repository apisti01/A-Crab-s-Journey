cmake_minimum_required(VERSION 3.16)
project(ACrabsJourney)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
set(BUILD_SHARED_LIBS OFF)
endif()
#add the directory for the unit testing
add_subdirectory(test)

if (WIN32)
    
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG 2.5.1)
    FetchContent_MakeAvailable(SFML)

else()

    set(SFML_STATIC_LIBRARIES, TRUE)
    find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

endif()

# core library
add_library(core AnimatedSprite.cpp AnimatedSprite.h Bullet.cpp Bullet.h Consumable.cpp Consumable.h Enemy.cpp Enemy.h
        FloorMap.cpp FloorMap.h GameCharacter.cpp GameCharacter.h Item.cpp Item.h MeleeWeapon.cpp MeleeWeapon.h
        Obstacle.cpp Obstacle.h Player.cpp Player.h RangedWeapon.cpp RangedWeapon.h Room.cpp Room.h
        StaticRangedEnemy.cpp StaticRangedEnemy.h Weapon.cpp Weapon.h Wearable.cpp Wearable.h)
target_link_libraries(core PUBLIC sfml-graphics sfml-audio)

# executable file
add_executable(ACrabsJourney main.cpp)
target_link_libraries(ACrabsJourney PRIVATE core)