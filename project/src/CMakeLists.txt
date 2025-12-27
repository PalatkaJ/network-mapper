cmake_minimum_required(VERSION 3.31)
project(network-mapper)

set(CMAKE_CXX_STANDARD 23)

find_package(PcapPlusPlus REQUIRED)
find_package(cxxopts REQUIRED)

add_executable("${PROJECT_NAME}" main.cpp
        Application/ApplicationConstants.hpp
        Application/ApplicationController.cpp
        Application/ApplicationController.hpp
        RequestProcessors/RequestProcessor.cpp
        RequestProcessors/RequestProcessor.hpp
        RequestProcessors/NetworkScanner.cpp
        RequestProcessors/NetworkScanner.hpp
        Application/ScanRequest.cpp
        Application/ScanRequest.hpp)
set_target_properties("${PROJECT_NAME}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries("${PROJECT_NAME}" PUBLIC PcapPlusPlus::Pcap++)
target_link_libraries("${PROJECT_NAME}" PUBLIC cxxopts::cxxopts)
