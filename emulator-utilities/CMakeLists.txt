add_library(emulator_utilities)

target_sources(emulator_utilities PRIVATE
    src/ProgramUtil.cpp
    src/RandomUtil.cpp
    src/ColorUtils.cpp
)

target_include_directories(emulator_utilities PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_link_libraries(emulator_utilities PUBLIC emulator_shared)

target_warnings(emulator_utilities)

if(ENABLE_SANITIZERS)
    target_sanitizers(emulator_utilities)
endif()

if (BUILD_TESTING)
    file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

    if (TEST_SOURCES)
        add_executable(emulator_utilities_tests ${TEST_SOURCES})

        target_link_libraries(emulator_utilities_tests PRIVATE emulator_utilities emulator_shared gtest gtest_main)

        target_warnings(emulator_utilities_tests)

        if(ENABLE_SANITIZERS)
            target_sanitizers(emulator_utilities_tests)
        endif()

        add_test(
            NAME emulator_utilities_tests 
            COMMAND emulator_utilities_tests)

        endif()
endif()
