# Enable common sanitizers for supported compilers.
function(enable_sanitizers target)
  if (DEFINED ENABLE_SANITIZERS AND ENABLE_SANITIZERS)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
      target_compile_options(${target} PRIVATE -fsanitize=address,undefined)
      target_link_options(${target}    PRIVATE -fsanitize=address,undefined)
      # Optional: nicer ASan output
      if (UNIX AND NOT APPLE)
        target_link_options(${target} PRIVATE -fno-omit-frame-pointer)
        target_compile_options(${target} PRIVATE -fno-omit-frame-pointer)
      endif()
    endif()
  endif()
endfunction()

# --- Back-compat alias: some subdirs call target_sanitizers(<tgt>)
function(target_sanitizers target)
  enable_sanitizers(${target})
endfunction()
