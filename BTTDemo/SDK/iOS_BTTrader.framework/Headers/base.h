#pragma once

#include "util.h"
#include "time_spec.h"
#include "cripemd160.h"
#include "sha256.h"
#include "sha512.h"
#include "ec_private.hpp"
#include "decimal.h"

using namespace std;

namespace bytetrade {
    
    bytes string_to_bytes( string val );
    
    bytes uint8_to_bytes(uint8_t value);
    bytes uint32_to_bytes(uint32_t value);
    bytes uint64_to_bytes(uint64_t value);
    bytes uint128_to_bytes(uint128_t value);
    bytes bool_to_bytes(bool value);
    bytes optional_uint128_to_bytes(optional<uint128_t> value);
    bytes optional_time_spec_to_bytes(optional<time_spec> value);
    bytes optional_string_to_bytes(optional<string> value);
    bytes optional_ripemd160_to_bytes(optional<ripemd160> value);
    
    void print_bytes(bytes b);
    // bytes idto_eth_signbytes(string s);
    // bytes stringto_eth_signbytes(string s);
    // bytes tokento_eth_signbytes(string s);
    // bytes numberto_eth_signbytes(uint64_t s);
    std::string to_hex(const char *d, uint32_t s);
    std::string to_hex(const bytes &data);
    
    
    string get_sha256_hash(bytes bb);
    bytes sha256(bytes bb);
    
//    string get_private_key_string_from_mnemonic(string mnemonicString);
    libbitcoin::ec_secret get_private_key(string private_key_secret);
    libbitcoin::ec_secret get_private_key_from_mnemonic(string mnemonicString);
    libbitcoin::wallet::ec_public get_public_key_from_secret(libbitcoin::ec_secret secret);
    string get_address(libbitcoin::wallet::ec_public pky);
    string get_pub_key_string(libbitcoin::wallet::ec_public pky);
    string sign(libbitcoin::ec_secret secret, string hash);
    string sign(libbitcoin::ec_secret secret, bytes hash);
    
    string to_string(const uint128_t d);
    uint128_t get_decimal(const string dec, const string base);
    
}

bytetrade::bytes operator+(bytetrade::bytes a, bytetrade::bytes b);

