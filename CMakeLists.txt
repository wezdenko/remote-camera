cmake_minimum_required(VERSION 2.8)
set(CMAKE_TOOLCHAIN_FILE /home/swo/Desktop/BR_Internet_Radio/QemuVirt64/buildroot-2020.02/output/host/share/buildroot/toolchainfile.cmake)
project(SKPS_Project)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${OpenCV_INCLUDE_DIRS} lib)

add_subdirectory(lib)
add_subdirectory(movementDetector)
add_subdirectory(pathCreator)
add_subdirectory(server)

set_property(TARGET movementDetector PROPERTY CMAKE_CXX_CLANG_TIDY)
set_property(TARGET pathCreator PROPERTY CMAKE_CXX_CLANG_TIDY)
set_property(TARGET ServerApp PROPERTY CMAKE_CXX_CLANG_TIDY)
