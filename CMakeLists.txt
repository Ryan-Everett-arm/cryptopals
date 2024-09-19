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
    library/helpers/challengeList.h
    library/helpers/random.c
)

set(
    MbedTLS_DIR
    $ENV{MBEDTLS_CMAKE}
)

set(
    OPENSSL_ROOT_DIR
    /usr/include/openssl
)

find_package(OpenSSL REQUIRED)

find_package(MbedTLS REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/library/helpers
     MbedTLS::mbedtls/include
)
link_directories(
    ${CMAKE_SOURCE_DIR}/library/helpers
)

#May eventually replace with a single executable which takes challenge number
#as param.

#Set 1:
add_executable(challenge1 library/set1/challenge1.c ${Helpers})
add_executable(challenge2 library/set1/challenge2.c ${Helpers})
add_executable(challenge3 library/set1/challenge3.c ${Helpers})
add_executable(challenge4 library/set1/challenge4.c ${Helpers})
add_executable(challenge5 library/set1/challenge5.c ${Helpers})
add_executable(challenge6 library/set1/challenge6.c ${Helpers})
add_executable(challenge7 library/set1/challenge7.c ${Helpers})
add_executable(challenge7SSL library/set1/challenge7SSL.c ${Helpers})
add_executable(challenge8 library/set1/challenge8.c ${Helpers})

#Set 2:
add_executable(challenge9 library/set2/challenge9.c ${Helpers})
add_executable(challenge10 library/set2/challenge10.c ${Helpers})
add_executable(challenge11 library/set2/challenge11.c ${Helpers})

#Link external libraries
target_link_libraries(challenge1 MbedTLS::mbedtls)
target_link_libraries(challenge2 MbedTLS::mbedtls)
target_link_libraries(challenge3 MbedTLS::mbedtls)
target_link_libraries(challenge4 MbedTLS::mbedtls)
target_link_libraries(challenge5 MbedTLS::mbedtls)
target_link_libraries(challenge6 MbedTLS::mbedtls)
target_link_libraries(challenge7 MbedTLS::mbedtls)
# target_link_libraries(challenge7SSL OpenSSL::SSL)
target_link_libraries(challenge8 MbedTLS::mbedtls)
target_link_libraries(challenge9 MbedTLS::mbedtls)
target_link_libraries(challenge10 MbedTLS::mbedtls)
target_link_libraries(challenge11 MbedTLS::mbedtls)
