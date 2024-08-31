cmake_minimum_required(VERSION 3.12)
project(delivery CXX)

# Adding userver dependency
find_package(userver COMPONENTS core postgresql QUIET)

# Enable userver libraries that are needed in this project
set(USERVER_FEATURE_POSTGRESQL ON CACHE BOOL "" FORCE)

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
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/*.hpp" "src/*.cpp")
list(FILTER ${PROJECT_NAME}_SOURCES EXCLUDE REGEX ".*_test\\.cpp|hpp$")
list(FILTER ${PROJECT_NAME}_SOURCES EXCLUDE REGEX ".*_mock\\.cpp|hpp$")
list(FILTER ${PROJECT_NAME}_SOURCES EXCLUDE REGEX ".*main\\.cpp$")
add_library(${PROJECT_NAME}_objs OBJECT ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME}_objs PUBLIC src)

# Dependencies
target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver-core userver::postgresql)

# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)


# Unit Tests
file(GLOB_RECURSE ${PROJECT_NAME}_UNITTESTS "src/*_test.cpp" "src/*_mock.cpp")
add_executable(${PROJECT_NAME}_unittest ${${PROJECT_NAME}_UNITTESTS})
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
