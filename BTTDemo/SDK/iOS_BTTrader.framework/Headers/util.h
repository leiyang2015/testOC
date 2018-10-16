#pragma once

#include "jsonxx.h"
#include "optional.h"
#include "uint128.h"
#include "vector_ref.h"
#include <cassert>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <sstream>
#include <string>

using namespace std;

namespace bytetrade {
    // Binary data types.
    using byte = uint8_t;
    using bytes = std::vector<byte>;
    using bytesRef = vector_ref<byte>;
    using bytesConstRef = vector_ref<byte const>;
    
    typedef string account_id_type;
    
    template <class T, class Out>
    inline void toBigEndian(T _val, Out &o_out);
    template <class T, class In>
    inline T fromBigEndian(In const &_bytes);
    
    /// Converts a string to a byte array containing the string's (byte) data.
    inline bytes asBytes(std::string const &_b) {
        return bytes((byte const *) _b.data(), (byte const *) (_b.data() + _b.size()));
    }
    
    // template <class _T>
    // std::string asHex(_T const &_data, int _w = 2) {
    //     std::ostringstream ret;
    //     for (auto i : _data)
    //         ret << std::hex << std::setfill('0') << std::setw(_w) << (int) (typename std::make_unsigned<decltype(i)>::type) i;
    //     return ret.str();
    // }
    
    int fromHex(char _i);
    bytes fromUserHex(std::string const &_s);
    bytes toHex(std::string const &_s);
    
    size_t writevarint32(uint8_t *s, uint32_t n);
    size_t writevarint64(uint8_t *s, uint64_t n);
    
    
    
}

bytetrade::bytes operator+(bytetrade::bytes a, bytetrade::bytes b);

