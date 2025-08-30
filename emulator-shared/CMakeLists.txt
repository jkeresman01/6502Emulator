add_library(emulator_shared INTERFACE)
target_include_directories(emulator_shared INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
