cmake_minimum_required(VERSION 3.28)

project(hexcellent
    VERSION 1.0.0
    LANGUAGES CXX
)

option(HEXCELLENT_STATIC "Link the hexcellent binary statically" OFF)

include(GNUInstallDirs)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HEXCELLENT_RAYLIB_VERSION 6.2)

find_package(raylib ${HEXCELLENT_RAYLIB_VERSION} QUIET)

if(NOT raylib_FOUND)
    message(STATUS "raylib ${HEXCELLENT_RAYLIB_VERSION} not found on system, fetching it")

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        ${HEXCELLENT_RAYLIB_VERSION}
        GIT_SHALLOW    TRUE
        SYSTEM
    )
    FetchContent_MakeAvailable(raylib)
endif()

file(GLOB HEXCELLENT_SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(hexcellent ${HEXCELLENT_SOURCES})

target_include_directories(hexcellent
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(hexcellent
    PRIVATE
        HEXCELLENT_VERSION="${PROJECT_VERSION}"
)

target_compile_options(hexcellent
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
)

target_link_libraries(hexcellent PRIVATE raylib)

if(HEXCELLENT_STATIC)
    target_link_options(hexcellent PRIVATE -static)
endif()

install(TARGETS hexcellent RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
