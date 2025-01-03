cmake_minimum_required(VERSION 3.10)

# set project name and version
file(STRINGS ".version" VERSION_FILE)
project(spotify-connect-proxy VERSION ${VERSION_FILE} LANGUAGES CXX)

# require compiler features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# require external packages and programs
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTEST gtest>=1.11 IMPORTED_TARGET)
pkg_check_modules(SYSTEMD libsystemd>=247 REQUIRED IMPORTED_TARGET)

# import directory names used on GNU systems
include(GNUInstallDirs)

# include build scripts
include(src.cmake)

if (NOT GTEST_FOUND)
  message(WARNING "GoogleTest not found, not building unittests")
else ()
  message(STATUS "Found GoogleTest: ${GTEST_VERSION}")

  find_program(GCOVR gcovr)
  if (NOT GCOVR)
      message(WARNING "gcovr not found, no coverage report will be available")
  else ()
      message(STATUS "Found gcovr: ${GCOVR}")
  endif ()

  include(unittest.cmake)
endif ()
