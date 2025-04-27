cmake_minimum_required(VERSION 3.10)
project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)
set(EXTERNAL_DIR external)

add_subdirectory(${EXTERNAL_DIR}/glfw)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${EXTERNAL_DIR}/googletest)
enable_testing()

add_library(imgui STATIC
    ${EXTERNAL_DIR}/imgui/imgui.cpp
    ${EXTERNAL_DIR}/imgui/imgui_draw.cpp
    ${EXTERNAL_DIR}/imgui/imgui_tables.cpp
    ${EXTERNAL_DIR}/imgui/imgui_widgets.cpp
    ${EXTERNAL_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${EXTERNAL_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${EXTERNAL_DIR}/imgui
    ${EXTERNAL_DIR}/imgui/backends
    ${EXTERNAL_DIR}/glfw/include
)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE CORE_SOURCES
    ${SRC_DIR}/Core/*.cpp
    ${SRC_DIR}/Assembler/*.cpp
    ${SRC_DIR}/Disassembler/*.cpp
    ${SRC_DIR}/Util/*.cpp
    ${SRC_DIR}/Types/*.cpp
)

add_library(EmulatorCore STATIC ${CORE_SOURCES})
target_include_directories(EmulatorCore PUBLIC
    ${SRC_DIR}
    ${EXTERNAL_DIR}/imgui
    ${EXTERNAL_DIR}/imgui/backends
    ${EXTERNAL_DIR}/glfw/include
)


file(GLOB_RECURSE GUI_SOURCES
    ${SRC_DIR}/App/*.cpp
    ${SRC_DIR}/Components/*.cpp
    ${SRC_DIR}/Types/*.cpp
)

add_library(EmulatorApp STATIC ${GUI_SOURCES})
target_include_directories(EmulatorApp PUBLIC ${SRC_DIR})
target_link_libraries(EmulatorApp PRIVATE EmulatorCore imgui glfw OpenGL::GL)

add_executable(6502Emulator src/Main.cpp)
target_include_directories(6502Emulator PRIVATE
    ${SRC_DIR}
    ${EXTERNAL_DIR}/imgui
    ${EXTERNAL_DIR}/imgui/backends
    ${EXTERNAL_DIR}/glfw/include
)
target_link_libraries(6502Emulator PRIVATE EmulatorApp)

add_subdirectory(tests)
