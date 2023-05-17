cmake_minimum_required(VERSION 3.21)
if (APPLE)
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif()
project(Tetris LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(
    TetrisTest
    tests/test.cpp
)
target_link_libraries(
    TetrisTest
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(TetrisTest)

add_executable(Tetris src/main.cpp)
target_include_directories(Tetris PRIVATE includes)
target_link_libraries(Tetris PRIVATE sfml-graphics)
target_compile_features(Tetris PRIVATE cxx_std_20)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Tetris> $<TARGET_FILE_DIR:Tetris> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Tetris)
