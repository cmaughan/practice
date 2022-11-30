cmake_minimum_required(VERSION 3.2)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DEBUG_POSTFIX "-debug")
set(CMAKE_RELWITHDEBINFO_POSTFIX "-reldbg")

if (WIN32)
set(VCPKG_TARGET_TRIPLET x64-windows-static-md)
endif()
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project (Practice
    LANGUAGES CXX C
    VERSION 0.5.0)

# Used Packages
#include(m3rdparty/cmake/copy_files.cmake)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_LIST_DIR}/vcpkg/packages/mutils_${VCPKG_TARGET_TRIPLET}/lib/cmake/mutils)

find_package(gl3w REQUIRED)
find_package(gsl-lite REQUIRED)
find_package(sdl2 REQUIRED)
find_package(fmt REQUIRED)
find_package(imgui REQUIRED)
find_package(freetype CONFIG REQUIRED)
find_package(unofficial-concurrentqueue REQUIRED)
find_package(tinyfiledialogs REQUIRED)
find_package(mutils REQUIRED)
find_package(implot REQUIRED)

MESSAGE(STATUS " CMakeLists: Practice")

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Set all compiler flags
INCLUDE(cmake/all.cmake)
#INCLUDE(utils/list.cmake)
INCLUDE(advent_of_code/list.cmake)
#INCLUDE(rosalind/list.cmake)

SET(PRACTICE_ROOT ${CMAKE_CURRENT_LIST_DIR})

# config_app.h
CONFIGURE_FILE(${CMAKE_CURRENT_LIST_DIR}/cmake/config_app.h.cmake ${CMAKE_BINARY_DIR}/config_app.h)

MESSAGE(STATUS ${CPP_INCLUDE})
INCLUDE_DIRECTORIES(
    ${CPP_INCLUDE}
    ${CMAKE_BINARY_DIR}
    ./
    )

ADD_EXECUTABLE (${PROJECT_NAME}_Cpp WIN32 ${CPP_SOURCE} ${CMAKE_CURRENT_LIST_DIR}/dpiawarescaling.manifest main.cpp common.h)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}_Cpp
    opengl32
    SDL2::SDL2
    SDL2::SDL2main
    implot::implot
    MUtils::MUtils)

SOURCE_GROUP (utils REGULAR_EXPRESSION "utils/.*")
SOURCE_GROUP (advent_of_code\\2017 REGULAR_EXPRESSION "advent_of_code/2017.*")
SOURCE_GROUP (advent_of_code\\2018 REGULAR_EXPRESSION "advent_of_code/2018.*")
SOURCE_GROUP (advent_of_code\\2019 REGULAR_EXPRESSION "advent_of_code/2019.*")
SOURCE_GROUP (advent_of_code\\2020 REGULAR_EXPRESSION "advent_of_code/2020.*")
SOURCE_GROUP (advent_of_code\\2022 REGULAR_EXPRESSION "advent_of_code/2022.*")
SOURCE_GROUP (rosalind REGULAR_EXPRESSION "rosalind.*")
SOURCE_GROUP (app\\app REGULAR_EXPRESSION "(main.cpp|common.h)")
SOURCE_GROUP (app\\m3rdparty REGULAR_EXPRESSION "m3rdparty.*")
