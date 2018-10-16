#pragma once
 
#include <cstring>
#include <string>
#include <ctime>
#include "util.h"

namespace bytetrade {

struct time_spec {

    uint32_t value;

    time_spec() {
        value = 0;
    }

    time_spec(uint32_t n) {
        value = n;
    }

    static time_spec now() {
        time_spec s(time(NULL));
        return s;
    }

    bytes toBytes();

    std::string toString();
};
}