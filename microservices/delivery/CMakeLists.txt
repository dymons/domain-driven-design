cmake_minimum_required(VERSION 3.12)
project(delivery CXX)

# Compatibility mode: some systems don't support these features
set(USERVER_FEATURE_CRYPTOPP_BLAKE2 OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_GRPC_CHANNELZ OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_REDIS_HI_MALLOC ON CACHE BOOL "" FORCE)

# Disable compiler checks
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-enum-constexpr-conversion")

# Adding userver dependency
add_subdirectory(third_party/userver)
userver_setup_environment()

# Use C++23
set(CMAKE_CXX_STANDARD 23)

# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
    src/hello.hpp
    src/hello.cpp
    src/core/domain/shared_kernel/weight.hpp
    src/core/domain/shared_kernel/weight.cpp
    src/core/domain/shared_kernel/location.hpp
    src/core/domain/shared_kernel/location.cpp
    src/core/domain/shared_kernel/exceptions.hpp
    src/core/domain/shared_kernel/exceptions.cpp
)
target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver-core)


# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)


# Unit Tests
add_executable(${PROJECT_NAME}_unittest
    src/core/domain/shared_kernel/weight_test.cpp
    src/core/domain/shared_kernel/location_test.cpp
)
target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME}_objs userver-utest)
add_google_tests(${PROJECT_NAME}_unittest)


# Functional Tests
include(UserverTestsuite)

userver_testsuite_add_simple()


# Install
include(GNUInstallDirs)

if(DEFINED ENV{PREFIX})
  message(STATUS "Set install prefix: $ENV{PREFIX}")
  file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
  set(CMAKE_INSTALL_PREFIX "${PREFIX_PATH}")
endif()

file(GLOB CONFIGS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.yaml ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.json)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
install(FILES ${CONFIGS_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} COMPONENT ${PROJECT_NAME})
