add_executable(6502EmulatorApp
  src/Main.cpp
  src/Emulator.cpp
)

target_include_directories(6502EmulatorApp PRIVATE include)

target_link_libraries(6502EmulatorApp PRIVATE
  emulator_components
  emulator_core
  emulator_utilities
  emulator_shared
  imgui_lib
)

set_target_properties(6502EmulatorApp PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_warnings(6502EmulatorApp)

if(ENABLE_SANITIZERS)
    target_sanitizers(6502EmulatorApp)
endif()

if (BUILD_TESTING)
  file(GLOB APP_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

  if (APP_TESTS)
    add_executable(emulator_app_tests ${APP_TESTS})

    target_link_libraries(
        emulator_app_tests PRIVATE
        emulator_components 
        emulator_core 
        emulator_utilities 
        emulator_shared 
        gtest 
        gtest_main)

    target_warnings(emulator_app_tests)

    if(ENABLE_SANITIZERS)
        target_sanitizers(emulator_app_tests)
    endif()

    add_test(NAME emulator_app_tests COMMAND emulator_app_tests)
  endif()
endif()
