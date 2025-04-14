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
 "src/Components/SwitchPanel/SwitchPanel.h" "src/Components/SwitchPanel/SwitchPanel.cpp")

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

add_executable(6502Emulator ${PROJECT_SOURCES} 
    "src/Assembler/Assembler.h"
    "src/Assembler/Assembler.cpp"
    "src/Util/ColorUtils.cpp"
    "src/Util/RandomUtil.h"
    "src/Util/RandomUtil.cpp"
    "src/Components/AbstractComponent.h"
    "src/Components/PixelDisplay/Pixel.h"
    "src/Components/PixelDisplay/Pixel.cpp"
    "src/Components/PixelDisplay/PixelDisplay.h"
    "src/Components/PixelDisplay/PixelDisplay.cpp"
    "src/Components/HEXDisplay/HEXDisplay.h"
    "src/Components/HEXDisplay/HEXDisplay.cpp"
    "src/Components/LEDs/LEDs.h"
    "src/Components/LEDs/LEDs.cpp"
    "src/Util/ProgramUtil.h"
    "src/Util/ProgramUtil.cpp"
    "src/Components/SwitchPanel/SwitchPanel.h"
    "src/Components/SwitchPanel/SwitchPanel.cpp"
)

target_include_directories(6502Emulator PRIVATE ${SRC_DIR})
target_include_directories(6502Emulator PRIVATE ${EXTERNAL_DIR}/imgui)
target_include_directories(6502Emulator PRIVATE ${EXTERNAL_DIR}/glfw/include)

target_link_libraries(6502Emulator PRIVATE imgui glfw OpenGL::GL)
