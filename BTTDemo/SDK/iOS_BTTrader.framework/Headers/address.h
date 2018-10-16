#pragma once
#include "base_58.hpp"
#include "base.h"
#include <string>
namespace bytetrade {
    
    class bytetrade_public_key {
    public:
        libbitcoin::wallet::ec_public pub;
        
        bytetrade_public_key() {
        }
        
        bytetrade_public_key(std::string pk);
        
        std::string toString() {
            return get_pub_key_string(pub);
        }
        
        std::string getAddress() {
            return get_address(pub);
        }
        
    };
    
    class address {
    public:
        string addr;
        
        address() {
        }
        
        address(std::string a);
        
        std::string getAddress() {
            return addr;
        }
    };
}
