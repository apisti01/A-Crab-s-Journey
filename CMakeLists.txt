cmake_minimum_required(VERSION 3.16)
project(ACrabsJourney)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(BUILD_SHARED_LIBS OFF)
endif()


# group the source files in the directory dedicated to the Game's states
set(STATES_SOURCE_FILES States_source_files/State.cpp States_source_files/State.h
        States_source_files/StateTitleScreen.cpp States_source_files/StateTitleScreen.h
        States_source_files/StateMainMenu.cpp States_source_files/StateMainMenu.h States_source_files/StatePlay.cpp
        States_source_files/StatePlay.h States_source_files/StateDisplayMap.cpp States_source_files/StateDisplayMap.h
        States_source_files/StatePause.cpp States_source_files/StatePause.h States_source_files/StateShop.cpp
        States_source_files/StateShop.h States_source_files/StatePearlShop.cpp States_source_files/StatePearlShop.h
        States_source_files/StateSettings.cpp States_source_files/StateSettings.h
        States_source_files/StateManageInventory.cpp States_source_files/StateManageInventory.h
        States_source_files/StateBestiary.cpp States_source_files/StateBestiary.h
        States_source_files/StatePrepareRun.cpp States_source_files/StatePrepareRun.h
        States_source_files/StateGameOver.cpp States_source_files/StateGameOver.h)

# group the source files in the directory dedicated to the enemies
set(ENEMY_SOURCE_FILES Enemy_source_files/Enemy.cpp Enemy_source_files/Enemy.h Enemy_source_files/StaticRangedEnemy.cpp
        Enemy_source_files/StaticRangedEnemy.h Enemy_source_files/AggressiveMeleeEnemy.cpp
        Enemy_source_files/AggressiveMeleeEnemy.h Enemy_source_files/DefensiveMeleeEnemy.cpp
        Enemy_source_files/DefensiveMeleeEnemy.h Enemy_source_files/ChasingRangedEnemy.cpp
        Enemy_source_files/ChasingRangedEnemy.h Enemy_source_files/EnemyFactory.cpp Enemy_source_files/EnemyFactory.h)

# core library
add_library(core STATIC ${STATES_SOURCE_FILES} ${ENEMY_SOURCE_FILES} AnimatedSprite.cpp AnimatedSprite.h Bullet.cpp Bullet.h
        Consumable.cpp Consumable.h FloorMap.cpp FloorMap.h GameCharacter.cpp GameCharacter.h Item.cpp Item.h
        MeleeWeapon.cpp MeleeWeapon.h Obstacle.cpp Obstacle.h Player.cpp Player.h RangedWeapon.cpp RangedWeapon.h
        Room.cpp Room.h Weapon.cpp Weapon.h Wearable.cpp Wearable.h Game.cpp Game.h Collider.cpp Collider.h Observer.cpp
        Observer.h Bestiary.cpp Bestiary.h GlobalProgress.cpp GlobalProgress.h Button.cpp Button.h SpriteButton.cpp
        SpriteButton.h TextButton.cpp TextButton.h)

# set SFML library
if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR SFML/lib/cmake/SFML)
    find_package(SFML COMPONENTS system window graphics audio REQUIRED)
    include_directories(SFML/include)
    target_link_libraries(core PUBLIC sfml-system sfml-window sfml-graphics sfml-audio)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
else()
    include_directories(/usr/local/include)
    find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
    include_directories(${SFML_INCLUDE_DIRS})
    target_link_libraries(core sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
endif()

# executable file
set(APP_ICON "Assets/Icon.rc")
add_executable(ACrabsJourney main.cpp ${APP_ICON})
target_link_libraries(ACrabsJourney PUBLIC core)