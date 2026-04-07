[//]: # ( @page Technical Documentation )

# Technical Documentation

## Architectural flow
The entry point is inside the `src/main.cpp` file, we do not do much there, 
just initialize the command line parser and call the main application 
controller which than orchestrates the rest of the application. Based on the 
command line arguments, the application controller creates the corresponding 
request processor (arp scan or traceroute), which then takes care of the actual 
work. Mostly the processor is another orchestrator and gatherer of the 
information needed for the work (such as a netmask), which is then executed by some concrete handler. 
After the work is done, the application presents the result to the user in a human-readable 
ASCII format using some presenters.

## Source code organization
The source code is organized into three main parts:
- app – application controller (the orchestrator), common interface for both 
  arp-scan and traceroute, some factories, logger
- arp-scan – everything related to the arp-scan functionality, from the 
  request processor to the result presentation
- traceroute – everything related to the traceroute functionality
Detailed documentation of each class is provided in the generated Doxygen 
  documentation.

## Implementation Problematics and Solutions
I decided that I did not want to spend too much time on parsing the command 
line arguments, which meant using some external library. I chose `cxxopts` 
because it seemed fast and easy to use. For the network packets management, 
I chose PcapPlusPlus library because it seemed to be the most complete 
and documented library – with a lot of examples as well, which made it easy 
to understand how to use it. Also note some design patterns used in the code,
e.g., the factory pattern for request processor/ logger creations 
or template method used for the presentation of the results.
### Arp scan
Implementing the arp scanning functionality using PcapPlusPlus library was 
rather easy (after learning the API, which took some time, of course). It 
provides a very nice API for working with packets and their metadata. Once 
the user specifies the interface they want to scan on, `PcapPlusPlus` gets 
you a lot of information about such an interface. All I had to find manually 
was the netmask of the interface for the arp scanner to be efficient (and 
search only those addresses that belong to the network). Then it was just 
playing with the library API. You can see the packet crafting inside 
`src/arp-scan/ArpScanner.cpp` file (it is not that complicated, add the 
right layers and send the packet). What is nice about the library is that it 
lets you start the capture on some other than the main thread that it creates for 
you, and you do not have to worry about it. The capture ends after some timeout, which 
the user can specify using the `--timeout` option (some reasonable default 
is used). Which for now we do not really use (the code just sleeps), but it is 
nice to have, which can be seen in the traceroute implementation. Also note 
that I have decided to parse a .csv file with mac addresses to vendor 
mappings, which is used for the presentation of the results – it seemed 
interesting to see.
### Traceroute
Firstly, I had to take care of the domain name resolving if the user does 
not provide a correct IP but rather the domain name. After all, it was 
pretty simple; there are some c functions that do exactly that. Then the logic is 
quite simple: send a packet with a TTL incremented each time with the 
destination IP set and see what happens. I found two ways to do it:
- start the capture, send some packets with such incrementing TTL, wait for 
  the responses and then present the results to the user (that is exactly 
  what the official `traceroute` tool does)
- start the capture, send some packets with such incrementing TTL, but do 
  not wait for all other responses, just stop when we reach the destination 
  or when the timeout is reached.
I implemented the first approach first, which was way easier, the logic was 
  exactly the same as in the arp scanner, just a different way of filtering 
  the responses. The second approach I preferred and wanted to implement 
  because I was exhausted of how long the traceroute tool takes to finish. 
  For that I had to introduce some more advanced c++ concepts, such as 
  `std::mutex` and `std::condition_variable`. After some time I was able to 
  implement it, and it is much faster than the first approach (you can try 
  to compare it yourself). It also has 
  some downsides, such as the possibility of missing some responses, but 
  after some testing it seems to be working fine most of the time, and it 
  outputs exactly the same results as the official `traceroute` tool.