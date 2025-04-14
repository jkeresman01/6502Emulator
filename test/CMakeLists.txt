file(GLOB TEST_SOURCES *.cpp)

add_executable(6502Tests ${TEST_SOURCES})

target_include_directories(6502Tests PRIVATE ../src)
target_link_libraries(6502Tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(6502Tests)
