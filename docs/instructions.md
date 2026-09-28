# Network Mapper
Let me introduce you to Network Mapper. It is a command line tool for mapping 
network topology, it is written in C++, and it works on macOS and Linux 
machines. Let's dig into the functionality this 
tool provides, and then we will see how to use it.

## Arp Scanning
Using this functionality, you can scan the network for devices that are connected to 
it. For example, let's say you are connected to some wi-fi (at your home, 
university, office...) and you are interested in seeing how many other devices 
are connected as well. You can use Network Mapper to do this. It also allows 
you to see their IP and MAC addresses, and if you are lucky enough, it will 
also show you the device's vendor (e.g., Apple, Intel, ...). You specify 
on which interface you want to scan and for how long you want to 
scan. We will dig a little deeper into this later on.

## Traceroute
An extension to this project is the traceroute functionality. It allows you to 
see how many hops it takes to reach a destination domain name or IP address. 
Let me also introduce an example. I guess that you are using google.com a 
lot. Ever wondered how long it takes to reach it (in some network metric)? 
Well, you can use Network Mapper to do this; 
it helps you map the routers your packet to google.com goes 
through! It shows you the IP addresses of the routers, and it is really fast 
(you can compare it to the standard traceroute tool, which took a different 
approach to the same problem).

## Installing and building
Building Network Mapper is really easy. Firstly clone the repository:
```shell
git clone https://github.com/PalatkaJ/network-mapper.git
cd network-mapper
```
It is a standard CMake project, and it uses vcpkg to manage its dependencies. 
So make sure you have CMake and vcpkg installed, 
and also we will need to set an environment variable called 
`VCPKG_ROOT` to the path of the vcpkg installation. More on how to install vcpkg 
can be found [here](https://github.com/Microsoft/vcpkg.git). To export such 
an environment variable, you can use the following command:
```shell
export VCPKG_ROOT=/path/to/installed/vcpkg
```
Then, run `install.sh` script which will install all the dependencies using 
vcpkg and build the project. Finally, run `run.sh` 
script to run a simple example. 
Also note 
that this tool needs to run with root privileges due to the use of raw 
network packets. This simple example will be scanning on the default interface, 
which would be your local network (e.g., your wi-fi), for 5 seconds, and then 
it will print the results.

## Usage and examples
After running the `install.sh` script, the built executable is located in the 
`build` directory, so go ahead and take a look there. Note that after you
install everything, you can also build the project with CMake, using:
```shell
cmake -S . -B build && cmake --build build
```
You will see the executable `network-mapper` in there. Now you can play with 
it, just remember to run it with root privileges. A great start is to run 
`sudo ./network-mapper --help` to see the available options.
## Simple Arp Scanning Example
After running the following command (note that the interface you will want 
to scan on will depend on your OS, you can use `ifconfig` to find out - for 
macOS users, you can try en0): 
```shell
sudo ./network-mapper --interface en0 --timeout 2000
```
I got this output:
```
================================================================================
 ARP Scan Results
================================================================================
 Interface:        en0
 Source IPv4 Addr: 10.0.0.140
 Default Gateway:  10.0.0.138
 Netmask:          255.255.255.0
--------------------------------------------------------------------------------
 IP Address      MAC Address         Vendor
--------------------------------------------------------------------------------
 10.0.0.138     7c:f1:7e:31:b2:c0   TP-Link Systems Inc
 10.0.0.141     de:15:25:42:43:10   Unknown: locally administrated
 10.0.0.145     b6:e0:51:dc:29:01   Unknown: locally administrated
 10.0.0.139     b0:4a:39:30:17:87   Beijing Roborock Technology Co., Ltd.
================================================================================
```
As you can see, I got 4 devices connected to my network, and I also got 
their MAC addresses and IP addresses as well as their vendors. 10.0.0.138 is 
my default gateway (the router which is the gateway to the internet), and the 
netmask means how many bits are used for the network address (in other words,
how many devices can be connected to the network).

## Traceroute Example
After running the following command (note that you can use google.com as 
well as the destination IP address, the tool will either resolve it or use 
it as is):
```shell
sudo ./network-mapper --destination google.com -v -o out.txt
```
I got the following verbose output:
```
Resolving IP for domain name: google.com
Extracted destination IP addr: 142.251.38.142
Source IP used: 10.0.0.140
Interface that will be used: en0
Resolved gateway mac to: 7c:f1:7e:31:b2:c0
Start capturing ICMP replies
Sending ICMP requests
All ICMP requests sent
Waiting for ICMP replies
ICMP replies received, stop capture
Traceroute finished
```
and the content of `out.txt`:
```
================================================================================
 Traceroute Results
================================================================================
 Destination IP: 142.251.38.142
 Status:         Destination Reached
 Max Hops:       128
--------------------------------------------------------------------------------
 Hop   IP Address
--------------------------------------------------------------------------------
 1    10.0.0.138
 2    *
 3    10.84.81.193
 4    194.228.115.83
 5    90.182.79.28
 6    90.182.78.35
 7    194.228.115.67
 8    *
 9    *
 10   *
 11   *
 12   142.251.38.142
================================================================================
```
As you can see, I reached the destination in 12 hops. The first hop is my 
default gateway, and the last hop is the destination (google.com got resolved 
to 142.251.38.142).

### Technical details
We will use a separate documentation file for the technical details of the 
project. Please refer to it [here](detailed.md).

## Third party libraries
The third party libraries which Network Mapper
uses are:
- `cxxopts` for parsing command line arguments
- `PcapPlusPlus` for network packets manipulation
