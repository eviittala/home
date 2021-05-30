cmake_minimum_required(VERSION 3.8)

set(This Test)    
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)    
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_TYPE RelWithDebInfo)    

enable_testing()

add_subdirectory(googletest)

set(Sources
    Test.cpp
   )

add_executable(${This}
        ${Sources}
        )
    
set(GTEST_OS_WINDOWS_MINGW True)

target_link_libraries(${This} PUBLIC
        gtest_main
        )

add_test(
        NAME ${This}
        COMMAND ${This}
        )
