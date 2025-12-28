cmake_minimum_required(VERSION 3.20)
project(network-mapper)

set(CMAKE_CXX_STANDARD 23)

find_package(PcapPlusPlus REQUIRED)
find_package(cxxopts REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        PcapPlusPlus::Pcap++
        cxxopts::cxxopts
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")