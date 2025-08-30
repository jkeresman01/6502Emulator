cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE COMPONENT_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(emulator_components ${COMPONENT_SOURCES})

target_include_directories(emulator_components PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(emulator_components
  PUBLIC  emulator_shared emulator_core emulator_utilities imgui_lib
  PRIVATE glfw OpenGL::OpenGL
)

target_warnings(emulator_components)
enable_sanitizers(emulator_components)

if (BUILD_TESTING)
  file(GLOB_RECURSE COMPONENT_TESTS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
  )
  if (COMPONENT_TESTS)
    add_executable(emulator_components_tests ${COMPONENT_TESTS})
    target_link_libraries(emulator_components_tests PRIVATE
      emulator_components emulator_core emulator_shared imgui_lib gtest gtest_main
    )
    target_warnings(emulator_components_tests)
    enable_sanitizers(emulator_components_tests)
    add_test(NAME emulator_components_tests COMMAND emulator_components_tests)
  endif()
endif()

