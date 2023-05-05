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

add_executable(Tetris src/main.cpp)
target_include_directories(Tetris PRIVATE includes)
target_link_libraries(Tetris PRIVATE sfml-graphics)
target_compile_features(Tetris PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Tetris)
