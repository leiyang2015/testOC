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
#ifndef LIBBITCOIN_CHECKSUM_HPP
#define LIBBITCOIN_CHECKSUM_HPP

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include "compat.hpp"
#include "define.hpp"
#include "data.hpp"
#include "assert.hpp"
#include "endian.hpp"

namespace libbitcoin {

static BC_CONSTEXPR size_t checksum_size = sizeof(uint32_t);

#define WRAP_SIZE(payload_size) (payload_size + checksum_size + 1)
#define UNWRAP_SIZE(payload_size) (payload_size - checksum_size - 1)

/**
 * Concatenate several data slices into a single fixed size array and append a
 * checksum.
 */
template <size_t Size>
bool build_checked_array(byte_array<Size>& out,
    const std::initializer_list<data_slice>& slices);

/**
 * Appends a four-byte checksum into the end of an array.
 * Returns false if the array is too small to contain the checksum.
 */
template<size_t Size>
bool insert_checksum(byte_array<Size>& out);

/**
 * Unwrap a wrapped payload.
 * @param[out] out_version   The version byte of the wrapped data.
 * @param[out] out_payload   The payload of the wrapped data.
 * @param[in]  wrapped       The wrapped data to unwrap.
 * @return                   True if input checksum validates.
 */
template <size_t Size>
bool unwrap(uint8_t& out_version, byte_array<UNWRAP_SIZE(Size)>& out_payload,
    const std::array<uint8_t, Size>& wrapped);

/**
 * Unwrap a wrapped payload and return the checksum.
 * @param[out] out_version   The version byte of the wrapped data.
 * @param[out] out_payload   The payload of the wrapped data.
 * @param[out] out_checksum  The validated checksum of the wrapped data.
 * @param[in]  wrapped       The wrapped data to unwrap.
 * @return                   True if input checksum validates.
 */
template <size_t Size>
bool unwrap(uint8_t& out_version,
    byte_array<UNWRAP_SIZE(Size)>& out_payload, uint32_t& out_checksum,
    const std::array<uint8_t, Size>& wrapped);

/**
 * Wrap arbitrary data.
 * @param[in]  version  The version byte for the wrapped data.
 * @param[out] payload  The payload to wrap.
 * @return              The wrapped data.
 */
template <size_t Size>
std::array<uint8_t, WRAP_SIZE(Size)> wrap(uint8_t version,
    const std::array<uint8_t, Size>& payload);

/**
 * Appends a four-byte checksum of a data chunk to itself.
 */
BC_API void append_checksum(data_chunk& data);

/**
 * Generate a bitcoin hash checksum. Last 4 bytes of sha256(sha256(data))
 *
 * int(sha256(sha256(data))[-4:])
 */
BC_API uint32_t bitcoin_checksum(data_slice data);

/**
 * Verifies the last four bytes of a data chunk are a valid checksum of the
 * earlier bytes. This is typically used to verify base58 data.
 */
BC_API bool verify_checksum(data_slice data);


template <size_t Size>
bool build_checked_array(byte_array<Size>& out,
    const std::initializer_list<data_slice>& slices)
{
    return build_array(out, slices) && insert_checksum(out);
}

template<size_t Size>
bool insert_checksum(byte_array<Size>& out)
{
    if (out.size() < checksum_size)
        return false;

    data_chunk body(out.begin(), out.end() - checksum_size);
    const auto checksum = to_little_endian(bitcoin_checksum(body));
    std::copy_n(checksum.begin(), checksum_size, out.end() - checksum_size);
    return true;
}

// std::array<> is used in place of byte_array<> to enable Size deduction.
template <size_t Size>
bool unwrap(uint8_t& out_version,
    std::array<uint8_t, UNWRAP_SIZE(Size)>& out_payload,
    const std::array<uint8_t, Size>& wrapped)
{
    uint32_t unused;
    return unwrap(out_version, out_payload, unused, wrapped);
}

// std::array<> is used in place of byte_array<> to enable Size deduction.
template <size_t Size>
bool unwrap(uint8_t& out_version,
    std::array<uint8_t, UNWRAP_SIZE(Size)>& out_payload,
    uint32_t& out_checksum, const std::array<uint8_t, Size>& wrapped)
{
    if (!verify_checksum(wrapped))
        return false;

    out_version = slice<0, 1>(wrapped)[0];
    out_payload = slice<1, Size - checksum_size>(wrapped);
    const auto bytes = slice<Size - checksum_size, Size>(wrapped);
    out_checksum = from_little_endian_unsafe<uint32_t>(bytes.begin());
    return true;
}

// std::array<> is used in place of byte_array<> to enable Size deduction.
template <size_t Size>
std::array<uint8_t, WRAP_SIZE(Size)> wrap(uint8_t version,
    const std::array<uint8_t, Size>& payload)
{
    byte_array<WRAP_SIZE(Size)> out;
    build_array(out, { to_array(version), payload });
    insert_checksum(out);
    return out;
}


} // namespace libbitcoin

//#include <bitcoin/bitcoin/impl/math/checksum.ipp>

#endif

