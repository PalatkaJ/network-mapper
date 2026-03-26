cmake_minimum_required(VERSION 3.20)
project(network-mapper)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Find dependencies
find_package(PcapPlusPlus CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        PcapPlusPlus::Pcap++
        cxxopts::cxxopts
)

# Set runtime output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
