/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_BASE_58_HPP
#define LIBBITCOIN_BASE_58_HPP

#include <string>
#include "define.hpp"
#include "data.hpp"
#include "assert.hpp"

namespace libbitcoin {

BC_API bool is_base58(const char ch);
BC_API bool is_base58(const std::string& text);

/**
 * Converts a base58 string to a number of bytes.
 * @return false if the input is malformed, or the wrong length.
 */
template <size_t Size>
bool decode_base58(byte_array<Size>& out, const std::string &in);

/**
 * Converts a base58 string literal to a data array.
 * This would be better as a C++11 user-defined literal,
 * but MSVC doesn't support those.
 * TODO: determine if the sizing function is always accurate.
 */
template <size_t Size>
byte_array<Size * 733 / 1000> base58_literal(const char(&string)[Size]);

/**
 * Encode data as base58.
 * @return the base58 encoded string.
 */
BC_API std::string encode_base58(data_slice unencoded);

/**
 * Attempt to decode base58 data.
 * @return false if the input contains non-base58 characters.
 */
BC_API bool decode_base58(data_chunk& out, const std::string& in);

BC_API bool decode_base58_private(uint8_t* out, size_t out_size,
    const char* in);

template <size_t Size>
bool decode_base58(byte_array<Size>& out, const std::string &in)
{
    byte_array<Size> result;
    if (!decode_base58_private(result.data(), result.size(), in.data()))
        return false;

    out = result;
    return true;
}

// TODO: determine if the sizing function is always accurate.
template <size_t Size>
byte_array<Size * 733 / 1000> base58_literal(const char(&string)[Size])
{
    // log(58) / log(256), rounded up.
    byte_array<Size * 733 / 1000> out;
    DEBUG_ONLY(const auto success =) decode_base58_private(out.data(),
        out.size(), string);
    BITCOIN_ASSERT(success);
    return out;
}

} // namespace libbitcoin

//#include <bitcoin/bitcoin/impl/formats/base_58.ipp>

#endif

