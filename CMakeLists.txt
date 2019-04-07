cmake_minimum_required(VERSION 3.1.3)

project(SISOP2 VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)


set(SOURCES
    src/infra/repository/FileUserRepository.cpp
    src/server/File.cpp
    src/server/User.cpp
    )
set(TESTFILES
    tests/infra/repository/FileUserRepositoryTest.cpp
    tests/server/UserTest.cpp
    )

add_library(engine ${SOURCES})

target_include_directories(engine
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    )

add_executable(server app/server.cpp)
target_link_libraries(server PRIVATE engine pthread)

add_executable(client app/client.cpp)
target_link_libraries(client PRIVATE engine pthread)

target_compile_options(engine PRIVATE
    # clang/GCC warnings
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
    "-Wall" "-Wextra" >
    # MSVC warnings
    $<$<CXX_COMPILER_ID:MSVC>:
    "/Wall" >
    )

set_target_properties(engine server client PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    )

# add make target 'gtest'
set(TEST_MAIN unit_tests.x)
add_executable(${TEST_MAIN} ${TESTFILES})
target_link_libraries(${TEST_MAIN} googletest engine pthread)
add_custom_target(gtest
    COMMAND "${PROJECT_BINARY_DIR}/${TEST_MAIN}"
    DEPENDS ${TEST_MAIN})

include(CodeCoverage)

# init submodules
add_custom_target(git_update
    COMMAND git submodule init
    COMMAND git submodule update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )

# google-test
add_library(googletest
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/src/gtest_main.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock/src/gmock-all.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock/src/gmock_main.cc
    )
target_include_directories(googletest
    PUBLIC ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest
    PUBLIC ${PROJECT_SOURCE_DIR}/external/googletest/googlemock/include
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock
    )
add_dependencies(googletest git_update)
set_source_files_properties(
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/src/gtest_main.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock/src/gmock-all.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock/src/gmock_main.cc
    PROPERTIES GENERATED 1
    )
