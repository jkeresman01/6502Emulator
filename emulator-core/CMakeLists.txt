cmake_minimum_required(VERSION 3.16)

add_library(emulator_core)

target_sources(emulator_core PRIVATE
  src/CPU6502.cpp
  src/Memory.cpp
  src/Assembler.cpp
  src/Disassembler.cpp
  src/SoftwareLoader.cpp
)

target_include_directories(emulator_core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(emulator_core
  PUBLIC  emulator_shared
  PRIVATE emulator_utilities
)

target_warnings(emulator_core)
enable_sanitizers(emulator_core)

if (BUILD_TESTING)
  file(GLOB_RECURSE CORE_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
  if (CORE_TESTS)
    add_executable(emulator_core_tests ${CORE_TESTS})
    target_link_libraries(emulator_core_tests
      PRIVATE emulator_core emulator_utilities emulator_shared gtest gtest_main
    )
    target_warnings(emulator_core_tests)
    enable_sanitizers(emulator_core_tests)
    add_test(NAME emulator_core_tests COMMAND emulator_core_tests)
  endif()
endif()

