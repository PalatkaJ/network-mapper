#include "UserRequest.hpp"

#include <iostream>

bool netmap::UserRequest::isValid() const {
    bool some_spec = !std::empty(interface_name) || !std::empty(traceroute_destination);
    bool more_spec = !std::empty(interface_name) && !std::empty(traceroute_destination);

    return some_spec && !more_spec;
}
