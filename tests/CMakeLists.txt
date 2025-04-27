file(GLOB_RECURSE TEST_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_executable(6502Tests ${TEST_SOURCES} "cpu/LDYTests.cpp" "cpu/NOPTests.cpp" "cpu/INYTests.cpp" "cpu/INCTests.cpp" "cpu/DEXTests.cpp" "cpu/TAXTests.cpp" "cpu/TSXTests.cpp" "cpu/TYATests.cpp" "cpu/STXTests.cpp" "cpu/SECTests.cpp" "cpu/ROLTests.cpp" "cpu/EORTests.cpp" "cpu/CMPTests.cpp" "cpu/BITTests.cpp" "cpu/ANDTests.cpp" "cpu/ADCTests.cpp" "memory/MemoryTests.cpp" "util/ColorUtilTests.cpp" "util/ProgramUtilTests.cpp")

target_link_libraries(6502Tests PRIVATE 
    EmulatorCore 
    gtest 
    gtest_main
)

target_include_directories(6502Tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

add_test(NAME AllTests COMMAND 6502Tests)

