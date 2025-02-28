icmake_minimum_required(VERSION 3.10)

project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib/imgui)
add_subdirectory(lib/glfw)

include_directories(${CMAKE_SOURCE_DIR}/lib/imgui)
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES 
    src/main.cpp 
    src/Core/CPU6502.cpp 
    src/Core/Memory.cpp
    src/App/Emulator.cpp
    src/Util/Time.cpp
    src/Util/Logger.cpp
)

add_executable(6502Emulator ${SOURCES})

target_link_libraries(6502Emulator glfw imgui)

