add_executable(6502EmulatorApp
  src/Main.cpp
  src/Emulator.cpp
)

target_include_directories(6502EmulatorApp PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(6502EmulatorApp PRIVATE
  emulator_components
  emulator_core
  emulator_utilities
  emulator_shared
  imgui_lib
)

set_target_properties(6502EmulatorApp PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_warnings(6502EmulatorApp)
enable_sanitizers(6502EmulatorApp)

if (BUILD_TESTING)
  file(GLOB APP_TESTS CONFIGURE_DEPENDS
       "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
  if (APP_TESTS)
    add_executable(emulator_app_tests ${APP_TESTS})
    target_link_libraries(emulator_app_tests PRIVATE
      emulator_components
      emulator_core
      emulator_utilities
      emulator_shared
      imgui_lib
      gtest gtest_main
    )
    target_warnings(emulator_app_tests)
    enable_sanitizers(emulator_app_tests)
    add_test(NAME emulator_app_tests COMMAND emulator_app_tests)
  endif()
endif()

