#cmake version
cmake_minimum_required(VERSION 3.5)

#add and compile the google test directory
add_subdirectory(./lib/googletest)

#find headers for google test
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add tests source files
set(TEST_SOURCE_FILES runAllTests.cpp PlayerTest.cpp RoomTest.cpp FloorMapTest.cpp Obstacle.cpp)
#executable file
add_executable(runAllTests ${TEST_SOURCE_FILES})
target_link_libraries(runAllTests gtest gtest_main core)