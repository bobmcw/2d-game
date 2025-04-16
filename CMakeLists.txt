cmake_minimum_required(VERSION 3.28)
project(roguelike)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         11.0.2
)

FetchContent_MakeAvailable(fmt)

add_executable(main src/main.cpp
        src/Player.cpp
        src/Player.h
        src/Map_parser.cpp
        src/Map_parser.h
        src/Terrain.cpp
        src/Terrain.h
        src/Collision_detector.cpp
        src/Collision_detector.h
        src/ProjectileManager.cpp
        src/ProjectileManager.h
        src/Projectile.cpp
        src/Projectile.h)
#target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics fmt)
