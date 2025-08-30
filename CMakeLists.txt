cmake_minimum_required(VERSION 3.16)
project(6502Emulator LANGUAGES CXX)

option(BUILD_TESTING "Build tests" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(ENABLE_SANITIZERS "Enable ASan/UBSan" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/warnings.cmake)
include(cmake/sanitizers.cmake)

# Silence legacy OpenGL warning and prefer GLVND
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# External deps via submodules you already have
# GLFW
add_subdirectory(external/glfw)
# ImGui (build minimal static lib with glfw & opengl backends)
add_library(imgui_lib
  external/imgui/imgui.cpp
  external/imgui/imgui_draw.cpp
  external/imgui/imgui_tables.cpp
  external/imgui/imgui_widgets.cpp
  external/imgui/backends/imgui_impl_glfw.cpp
  external/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_lib PUBLIC
  external/imgui
  external/imgui/backends
)
target_link_libraries(imgui_lib PUBLIC glfw OpenGL::OpenGL)

# GTest (only when testing)
include(CTest)
if (BUILD_TESTING)
  add_subdirectory(external/googletest)
endif()

# Modules
add_subdirectory(emulator-shared)
add_subdirectory(emulator-utilities)
add_subdirectory(emulator-core)
add_subdirectory(emulator-components)
add_subdirectory(emulator-application)
