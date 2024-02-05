#
# CMake Toolchain file for crosscompiling on ARM.
#
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER "/usr/bin/aarch64-linux-gnu-gcc-11")
set(CMAKE_CXX_COMPILER "/usr/bin/aarch64-linux-gnu-g++-11")


set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE arm64)