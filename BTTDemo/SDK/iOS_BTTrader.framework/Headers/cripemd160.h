#pragma once
 
#include <cstring>
#include <string>
#include <ctime>
#include "util.h"

namespace bytetrade {

struct ripemd160 {

    string id;

    ripemd160() {

    }
    
    ripemd160(string value) {
       id = value;
    }

    
    bytes toBytes();

    std::string toString();
};
}