cmake_minimum_required(VERSION 3.16)

add_library(emulator_utilities)

target_sources(emulator_utilities PRIVATE
  src/ColorUtils.cpp
  src/ProgramUtil.cpp
  src/RandomUtil.cpp
)

target_include_directories(emulator_utilities PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(emulator_utilities
  PUBLIC emulator_shared imgui_lib emulator_core
)

target_warnings(emulator_utilities)
enable_sanitizers(emulator_utilities)

if (BUILD_TESTING)
  file(GLOB_RECURSE UTIL_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
  if (UTIL_TESTS)
    add_executable(emulator_utilities_tests ${UTIL_TESTS})
    target_link_libraries(emulator_utilities_tests PRIVATE
      emulator_utilities emulator_shared imgui_lib gtest gtest_main
    )
    target_warnings(emulator_utilities_tests)
    enable_sanitizers(emulator_utilities_tests)
    add_test(NAME emulator_utilities_tests COMMAND emulator_utilities_tests)
  endif()
endif()

