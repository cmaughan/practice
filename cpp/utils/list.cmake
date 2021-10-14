SET(CDIR ${CMAKE_CURRENT_LIST_DIR})

LIST(APPEND CPP_SOURCE
    ${CDIR}/fileutils.cpp
    ${CDIR}/fileutils.h
    ${CDIR}/ringitr.h
    ${CDIR}/stringutils.cpp
    ${CDIR}/stringutils.h
    ${CDIR}/utils.h
    ${CDIR}/utils.cpp
    )

LIST(APPEND CPP_INCLUDE
    ${CMAKE_CURRENT_LIST_DIR})
