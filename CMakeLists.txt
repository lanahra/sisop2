cmake_minimum_required(VERSION 3.1.3)

project(SISOP2 VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")
include(ConfigSafeGuards)
include(Colors)


set(SOURCES
        src/application/DefaultUserService.cpp
        src/application/DefaultPrinterService.cpp
        src/infra/handler/DownloadFileHandler.cpp
        src/infra/handler/ExitCommandHandler.cpp
        src/infra/handler/ListFileEntriesHandler.cpp
        src/infra/handler/ListClientEntriesCommandHandler.cpp
        src/infra/handler/ListServerEntriesCommandHandler.cpp
        src/infra/handler/ListServerEntriesResponseHandler.cpp
        src/infra/handler/RemoveFileCommandHandler.cpp
        src/infra/handler/RemoveFileHandler.cpp
        src/infra/messaging/AsyncMessageListener.cpp
        src/infra/messaging/AsyncMessageListenerFactory.cpp
        src/infra/messaging/BlockingCommandListener.cpp
        src/infra/messaging/BlockingMessageListener.cpp
        src/infra/messaging/ConnectionListener.cpp
        src/infra/messaging/SocketMessageStreamer.cpp
        src/infra/messaging/TcpSocket.cpp
        src/infra/repository/SystemFileRepository.cpp
        src/server/File.cpp
        src/server/User.cpp
        src/server/SystemClock.cpp
        )
set(TESTFILES
        tests/application/DefaultUserServiceTest.cpp
        tests/application/DefaultPrinterServiceTest.cpp
        tests/infra/messaging/BlockingCommandListenerTest.cpp
        tests/infra/handler/DownloadFileHandlerTest.cpp
        tests/infra/handler/DownloadFileRequestTest.cpp
        tests/infra/handler/DownloadFileResponseTest.cpp
        tests/infra/handler/ExitCommandHandlerTest.cpp
        tests/infra/handler/ListFileEntriesHandlerTest.cpp
        tests/infra/handler/ListFileEntriesResponseTest.cpp
        tests/infra/handler/ListClientEntriesCommandHandlerTest.cpp
        tests/infra/handler/ListServerEntriesCommandHandlerTest.cpp
        tests/infra/handler/ListServerEntriesResponseHandlerTest.cpp
        tests/infra/handler/RemoveFileRequestTest.cpp
        tests/infra/handler/RemoveFileHandlerTest.cpp
        tests/infra/handler/RemoveFileCommandHandlerTest.cpp
        tests/infra/messaging/AsyncMessageListenerTest.cpp
        tests/infra/messaging/BlockingMessageListenerTest.cpp
        tests/infra/messaging/ConnectionListenerTest.cpp
        tests/infra/messaging/MessageTest.cpp
        tests/infra/messaging/OpenListenerLoopTest.cpp
        tests/infra/messaging/SocketMessageStreamerTest.cpp
        tests/infra/messaging/TcpSocketTest.cpp
        tests/infra/repository/SystemFileRepositoryTest.cpp
        tests/server/FileEntryTest.cpp
        tests/server/FileTest.cpp
        tests/server/RemovedEntryTest.cpp
        tests/server/TimestampsTest.cpp
        tests/server/UserTest.cpp
        tests/server/SystemClockTest.cpp
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

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")

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

endif()
