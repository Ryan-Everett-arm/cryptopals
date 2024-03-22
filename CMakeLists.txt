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
)

include_directories(
    ${CMAKE_SOURCE_DIR}/library/helpers
)
link_directories(
    ${CMAKE_SOURCE_DIR}/library/helpers
)

add_executable(challenge1 library/set1/challenge1.c ${Helpers})