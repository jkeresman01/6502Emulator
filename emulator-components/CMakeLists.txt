add_library(emulator_components)

target_sources(emulator_components PRIVATE
    src/Editor.cpp
    src/HEXDisplay.cpp
    src/LEDs.cpp
    src/MemoryLayout.cpp
    src/PixelDisplay.cpp
    src/SwitchPanel.cpp
    src/Pixel.cpp
)
target_include_directories(emulator_components PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_link_libraries(emulator_components
    PUBLIC emulator_core emulator_shared imgui_lib
    PRIVATE emulator_utilities)

target_warnings(emulator_components)

if(ENABLE_SANITIZERS) 
    target_sanitizers(emulator_components) 
endif()

option(ENABLE_GUI_TESTS "Run GL/GLFW-dependent tests" OFF)

if (BUILD_TESTING)
    file(GLOB COMP_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    if (COMP_TESTS AND ENABLE_GUI_TESTS)
        add_executable(emulator_components_tests ${COMP_TESTS})
        target_link_libraries(emulator_components_tests PRIVATE emulator_components gtest gtest_main)
        target_warnings(emulator_components_tests)
        if(ENABLE_SANITIZERS) target_sanitizers(emulator_components_tests) endif()
                add_test(NAME emulator_components_tests COMMAND emulator_components_tests)
        endif()
endif()
