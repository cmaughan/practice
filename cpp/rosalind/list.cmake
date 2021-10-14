SET(CDIR ${CMAKE_CURRENT_LIST_DIR})

FILE(GLOB_RECURSE FOUND_SOURCE
    ${CDIR}/*.cpp
    ${CDIR}/*.h)

LIST(APPEND CPP_SOURCE
    ${FOUND_SOURCE}
    )

LIST(APPEND CPP_INCLUDE
    ${CMAKE_CURRENT_LIST_DIR})

