function(userver_is_cxx_compile_option_supported IS_SUPPORTED OPTION)
  include(CheckCXXCompilerFlag)
  string(REPLACE "-" "_" FLAG ${OPTION})
  string(REPLACE "=" "_" FLAG ${FLAG})
  set(FLAG "HAS${FLAG}")
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag("-Werror -Wunknown-warning-option ${OPTION}" "${FLAG}")
  else()
    check_cxx_compiler_flag("-Werror ${OPTION}" "${FLAG}")
  endif()

  set(${IS_SUPPORTED} ${${FLAG}} PARENT_SCOPE)

  if (${${FLAG}})
    message(STATUS "Checking " ${OPTION} " - found")
  else()
    message(STATUS "Checking " ${OPTION} " - not found")
  endif()
endfunction()

function(userver_target_cxx_compile_options_if_supported target visibility)
  foreach(OPTION ${ARGN})
    userver_is_cxx_compile_option_supported(IS_SUPPORTED ${OPTION})
    if (${IS_SUPPORTED})
      target_compile_options(${target} ${visibility} "$<$<COMPILE_LANGUAGE:CXX>:${OPTION}>")
    endif()
  endforeach()
endfunction()

function(userver_cxx_compile_options_if_supported)
  foreach(OPTION ${ARGN})
    userver_is_cxx_compile_option_supported(IS_SUPPORTED ${OPTION})
    if (${IS_SUPPORTED})
      add_compile_options(${target} "$<$<COMPILE_LANGUAGE:CXX>:${OPTION}>")
    endif()
  endforeach()
endfunction()
