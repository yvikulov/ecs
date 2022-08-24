cmake_minimum_required(VERSION 3.0.0)
project(ECS VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

include_directories(${SDL2_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")
include_directories(${PROJECT_NAME} "include/")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
