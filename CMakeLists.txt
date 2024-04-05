cmake_minimum_required(VERSION 3.7...3.28)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    Cryptopals
    VERSION 1.0
    DESCRIPTION "Ryan Everett's Cryptopals answers."
    LANGUAGES C)


set(
    Helpers
    library/helpers/formatters.c
    library/helpers/printers.h
    library/helpers/arithmatic.c
    library/helpers/crypto.c
)

include_directories(
    ${CMAKE_SOURCE_DIR}/library/helpers
)
link_directories(
    ${CMAKE_SOURCE_DIR}/library/helpers
)

add_executable(challenge1 library/set1/challenge1.c ${Helpers})
add_executable(challenge2 library/set1/challenge2.c ${Helpers})
add_executable(challenge3 library/set1/challenge3.c ${Helpers})
add_executable(challenge4 library/set1/challenge4.c ${Helpers})
add_executable(challenge5 library/set1/challenge5.c ${Helpers})