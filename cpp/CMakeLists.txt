cmake_minimum_required(VERSION 3.2)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT (Practice)

MESSAGE(STATUS " CMakeLists: Practice")

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Set all compiler flags 
INCLUDE(cmake/all.cmake)
INCLUDE(m3rdparty/list.cmake)
INCLUDE(utils/list.cmake)
INCLUDE(advent_of_code/list.cmake)

SET(PRACTICE_ROOT ${CMAKE_CURRENT_LIST_DIR})

# config_app.h
CONFIGURE_FILE(${CMAKE_CURRENT_LIST_DIR}/cmake/config_app.h.cmake ${CMAKE_BINARY_DIR}/config_app.h)

MESSAGE(STATUS ${CPP_INCLUDE})
INCLUDE_DIRECTORIES(
    ${CPP_INCLUDE}
    ${CMAKE_BINARY_DIR}
    ./
    ) 

ADD_EXECUTABLE (${PROJECT_NAME}_Cpp ${CPP_SOURCE} main.cpp common.h)

SOURCE_GROUP (utils REGULAR_EXPRESSION "utils/.*")
SOURCE_GROUP (advent_of_code\\2017 REGULAR_EXPRESSION "advent_of_code/2017.*")
SOURCE_GROUP (advent_of_code\\2018 REGULAR_EXPRESSION "advent_of_code/2018.*")
SOURCE_GROUP (app REGULAR_EXPRESSION "(main.cpp|common.h)")
SOURCE_GROUP (m3rdparty REGULAR_EXPRESSION "m3rdparty.*")
