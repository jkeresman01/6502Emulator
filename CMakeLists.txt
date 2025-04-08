cmake_minimum_required(VERSION 3.10)
project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)
set(EXTERNAL_DIR external)

add_subdirectory(${EXTERNAL_DIR}/glfw)

include_directories(${EXTERNAL_DIR}/glfw/include)

add_library(imgui STATIC
    ${EXTERNAL_DIR}/imgui/imgui.cpp
    ${EXTERNAL_DIR}/imgui/imgui_draw.cpp
    ${EXTERNAL_DIR}/imgui/imgui_tables.cpp
    ${EXTERNAL_DIR}/imgui/imgui_widgets.cpp
    ${EXTERNAL_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${EXTERNAL_DIR}/imgui/backends/imgui_impl_opengl3.cpp
  "src/Core/Assembler.h" "src/Core/Assembler.cpp")

target_include_directories(imgui PUBLIC
    ${EXTERNAL_DIR}/imgui
    ${EXTERNAL_DIR}/imgui/backends
    ${EXTERNAL_DIR}/glfw/include
)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES 
    ${SRC_DIR}/*.cpp 
    ${SRC_DIR}/*.h
)

add_executable(6502Emulator ${PROJECT_SOURCES}  "src/Core/Assembler.h" "src/Core/Assembler.cpp")

target_include_directories(6502Emulator PRIVATE ${SRC_DIR})
target_include_directories(6502Emulator PRIVATE ${EXTERNAL_DIR}/imgui)
target_include_directories(6502Emulator PRIVATE ${EXTERNAL_DIR}/glfw/include)

target_link_libraries(6502Emulator PRIVATE imgui glfw OpenGL::GL)
