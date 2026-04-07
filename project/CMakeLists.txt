cmake_minimum_required(VERSION 3.20)
project(network-mapper)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(PcapPlusPlus CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

set(SOURCES
        src/main.cpp
        src/app/ApplicationController.cpp
        src/app/InvalidRequestProcessor.cpp
        src/app/Logger.cpp
        src/app/LoggerFactory.cpp
        src/app/RequestProcessor.cpp
        src/app/RequestProcessorFactory.cpp
        src/app/ResultPrinter.cpp
        src/app/ResultPrinter.cpp
        src/app/UserRequest.cpp
        src/arp-scan/ArpDeviceInfo.cpp
        src/arp-scan/ArpReplyHandler.cpp
        src/arp-scan/ArpScanner.cpp
        src/arp-scan/ArpScanPrinter.cpp
        src/arp-scan/ArpScanProcessor.cpp
        src/arp-scan/DevWrapperForArpScan.cpp
        src/arp-scan/MacVendorMapper.cpp
        src/traceroute/DevWrapperForTraceroute.cpp
        src/traceroute/IcmpReplyHandler.cpp
        src/traceroute/RouteTracer.cpp
        src/traceroute/TracerouteProcessor.cpp
        src/traceroute/TracerouteResultPrinter.cpp
)

# Create executable target
add_executable(${PROJECT_NAME} ${SOURCES})

set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")

target_compile_definitions(network-mapper PRIVATE
        DATA_PATH="${DATA_DIR}"
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
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
