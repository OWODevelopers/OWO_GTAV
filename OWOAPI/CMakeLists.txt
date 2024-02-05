# Always set the cmake min version.
cmake_minimum_required(VERSION 3.0)

set (PROJECT_VERSION "2.0")

project(OWO VERSION ${PROJECT_VERSION})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


file(GLOB SRC_CONTROLLER Controller/*.cpp)
file(GLOB SRC_DOMAIN Domain/*.cpp)
file(GLOB SRC_INFRAESTRUCTURE Infraestructure/*.cpp)
file(GLOB SRC_OWO *.cpp)

add_library(OWO SHARED)
target_sources(OWO PRIVATE ${SRC_CONTROLLER} ${SRC_DOMAIN} ${SRC_INFRAESTRUCTURE} ${SRC_OWO})

set_target_properties(OWO
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
)

# Let's set compiler-specific flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # G++
    target_compile_options(OWO PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(OWO PRIVATE /EHsc /MD /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(OWO PRIVATE WIN_EXPORT)
endif()