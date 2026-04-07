# Network Mapper

## Project Goal

The goal of this project is to create a C++ console application that analyzes LAN (and optionally even outside LAN).
The program shall scan the LAN, provide basic information and visualize the topology in ascii format.

### Functionality

The program will use ARP scan for analyzing LAN, and optionally, for an extension it will use TTL probing outside LAN 
(lowering TTL for analyzing hops → build the path towards destination IP).

### OS

The program should run on macOS and Linux machines.
