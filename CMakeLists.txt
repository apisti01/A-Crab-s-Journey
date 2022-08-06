cmake_minimum_required(VERSION 3.16)
project(ACrabsJourney)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(BUILD_SHARED_LIBS OFF)
endif()

# add the directory for the unit testing
add_subdirectory(test)

# set SFML library
if(WIN32)
    # for Windows
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG 2.5.1)
    FetchContent_MakeAvailable(SFML)
else()
    # for other OS
    set(SFML_STATIC_LIBRARIES, TRUE)
    find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
endif()

# group the source files in the directory dedicated to the Game's states
set(STATES_SOURCE_FILES States_source_files/State.cpp States_source_files/State.h  States_source_files/StateTitleScreen.cpp
        States_source_files/StateTitleScreen.h States_source_files/StateMainMenu.cpp States_source_files/StateMainMenu.h
        States_source_files/StatePlay.cpp States_source_files/StatePlay.h States_source_files/StateDisplayMap.cpp
        States_source_files/StateDisplayMap.h States_source_files/StatePause.cpp States_source_files/StatePause.h States_source_files/StateShop.cpp
        States_source_files/StateShop.h States_source_files/StatePearlShop.cpp States_source_files/StatePearlShop.h
        States_source_files/StateSettings.cpp States_source_files/StateSettings.h States_source_files/StateManageInventory.cpp
        States_source_files/StateManageInventory.h )

# group the source files in the directory dedicated to the enemies
set(ENEMY_SOURCE_FILES Enemy_source_files/Enemy.cpp Enemy_source_files/Enemy.h Enemy_source_files/StaticRangedEnemy.cpp
        Enemy_source_files/StaticRangedEnemy.h Enemy_source_files/AggressiveMeleeEnemy.cpp Enemy_source_files/AggressiveMeleeEnemy.h
        Enemy_source_files/DefensiveMeleeEnemy.cpp Enemy_source_files/DefensiveMeleeEnemy.h Enemy_source_files/ChasingRangedEnemy.cpp
        Enemy_source_files/ChasingRangedEnemy.h Enemy_source_files/EnemyFactory.cpp Enemy_source_files/EnemyFactory.h)

# core library
add_library(core ${STATES_SOURCE_FILES} ${ENEMY_SOURCE_FILES} AnimatedSprite.cpp AnimatedSprite.h Bullet.cpp Bullet.h Consumable.cpp Consumable.h
        FloorMap.cpp FloorMap.h GameCharacter.cpp GameCharacter.h Item.cpp Item.h MeleeWeapon.cpp MeleeWeapon.h
        Obstacle.cpp Obstacle.h Player.cpp Player.h RangedWeapon.cpp RangedWeapon.h Room.cpp Room.h
        Weapon.cpp Weapon.h Wearable.cpp Wearable.h Game.cpp Game.h Collider.cpp Collider.h)
target_link_libraries(core PUBLIC sfml-graphics sfml-audio)

# executable file
add_executable(ACrabsJourney main.cpp)
target_link_libraries(ACrabsJourney PRIVATE core)