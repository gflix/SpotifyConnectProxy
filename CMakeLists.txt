cmake_minimum_required(VERSION 3.10)

# set project name and version
file(STRINGS ".version" VERSION_FILE)
project(spotify-connect-proxy VERSION ${VERSION_FILE} LANGUAGES CXX)

# require compiler features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# require external packages and programs
find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD systemd>=247 REQUIRED IMPORTED_TARGET)

# import directory names used on GNU systems
include(GNUInstallDirs)

include(src.cmake)
