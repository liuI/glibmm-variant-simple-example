cmake_minimum_required(VERSION 3.0.0)
project(variant VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(glibmm glibmm-2.4 giomm-2.4 REQUIRED)

include_directories(${glibmm_INCLUDE_DIRS})

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} pthread ${glibmm_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
