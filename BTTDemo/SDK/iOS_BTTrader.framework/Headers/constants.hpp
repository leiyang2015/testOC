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
#ifndef LIBBITCOIN_CONSTANTS_HPP
#define LIBBITCOIN_CONSTANTS_HPP

#include <cstddef>
#include <cstdint>
#include "compat.hpp"
//#include "config/checkpoint.hpp"
#include "define.hpp"
#include "math/hash.hpp"
#include "message/network_address.hpp"
#include "version.hpp"

namespace libbitcoin {

// This guards assumptions within the codebase.
static_assert(sizeof(size_t) == sizeof(uint32_t) || 
    sizeof(size_t) == sizeof(uint64_t), "unsupported size_t");

#define BC_USER_AGENT "/libbitcoin:" LIBBITCOIN_VERSION "/"

// Generic constants.
//-----------------------------------------------------------------------------

BC_CONSTEXPR int64_t min_int64 = MIN_INT64;
BC_CONSTEXPR int64_t max_int64 = MAX_INT64;
BC_CONSTEXPR int32_t min_int32 = MIN_INT32;
BC_CONSTEXPR int32_t max_int32 = MAX_INT32;
BC_CONSTEXPR uint64_t max_uint64 = MAX_UINT64;
BC_CONSTEXPR uint32_t max_uint32 = MAX_UINT32;
BC_CONSTEXPR uint16_t max_uint16 = MAX_UINT16;
BC_CONSTEXPR uint8_t max_uint8 = MAX_UINT8;
BC_CONSTEXPR uint64_t max_size_t = BC_MAX_SIZE;
BC_CONSTEXPR uint8_t byte_bits = 8;

// Consensus sentinels.
//-----------------------------------------------------------------------------

BC_CONSTEXPR uint32_t no_previous_output = max_uint32;
BC_CONSTEXPR uint32_t max_input_sequence = max_uint32;
BC_CONSTEXPR uint64_t sighash_null_value = max_uint64;

// Script/interpreter constants.
//-----------------------------------------------------------------------------

// Consensus
BC_CONSTEXPR size_t max_counted_ops = 201;
BC_CONSTEXPR size_t max_stack_size = 1000;
BC_CONSTEXPR size_t max_script_size = 10000;
BC_CONSTEXPR size_t max_push_data_size = 520;
BC_CONSTEXPR size_t max_script_public_keys = 20;
BC_CONSTEXPR size_t multisig_default_sigops = 20;
BC_CONSTEXPR size_t max_number_size = 4;
BC_CONSTEXPR size_t max_check_locktime_verify_number_size = 5;
BC_CONSTEXPR size_t max_check_sequence_verify_number_size = 5;

// Policy.
BC_CONSTEXPR size_t max_null_data_size = 80;

// Various validation constants.
//-----------------------------------------------------------------------------

BC_CONSTEXPR size_t min_coinbase_size = 2;
BC_CONSTEXPR size_t max_coinbase_size = 100;
BC_CONSTEXPR size_t coinbase_maturity = 100;
BC_CONSTEXPR size_t median_time_past_interval = 11;
BC_CONSTEXPR size_t locktime_threshold = 500000000;
BC_CONSTEXPR size_t max_block_size = 1000000;
BC_CONSTEXPR size_t max_sigops_factor = 50;
BC_CONSTEXPR size_t max_block_sigops = max_block_size / max_sigops_factor;

// Relative locktime constants.
//-----------------------------------------------------------------------------

BC_CONSTEXPR size_t relative_locktime_min_version = 2;
BC_CONSTEXPR size_t relative_locktime_seconds_shift = 9;
BC_CONSTEXPR uint32_t relative_locktime_mask = 0x0000ffff;
BC_CONSTEXPR uint32_t relative_locktime_disabled = 0x80000000;
BC_CONSTEXPR uint32_t relative_locktime_time_locked = 0x00400000;

// Fork constants.
//-----------------------------------------------------------------------------

// Mainnet frozen activation heights (frozen_activations).
BC_CONSTEXPR size_t mainnet_bip34_freeze = 227931;

// Testnet frozen activation heights (frozen_activations).
BC_CONSTEXPR size_t testnet_bip34_freeze = 21111;

// Regtest (arbitrary) frozen activation heights (frozen_activations).
BC_CONSTEXPR size_t regtest_bip34_freeze = 0;


// Network protocol constants.
//-----------------------------------------------------------------------------

// Explicit size.
BC_CONSTEXPR size_t command_size = 12;

// Explicit limits.
BC_CONSTEXPR size_t max_address = 1000;
BC_CONSTEXPR size_t max_filter_add = 520;
BC_CONSTEXPR size_t max_filter_functions = 50;
BC_CONSTEXPR size_t max_filter_load = 36000;
BC_CONSTEXPR size_t max_get_blocks = 500;
BC_CONSTEXPR size_t max_get_headers = 2000;
BC_CONSTEXPR size_t max_get_data = 50000;
BC_CONSTEXPR size_t max_inventory = 50000;

/**
 * The minimum safe length of a seed in bits (multiple of 8).
 */
BC_CONSTEXPR size_t minimum_seed_bits = 128;

/**
 * The minimum safe length of a seed in bytes (16).
 */
BC_CONSTEXPR size_t minimum_seed_size = minimum_seed_bits / byte_bits;

// Effective limit given a 32 bit chain height boundary: 10 + log2(2^32) + 1.
BC_CONSTEXPR size_t max_locator = 43;

// Variable integer prefix sentinels.
BC_CONSTEXPR uint8_t varint_two_bytes = 0xfd;
BC_CONSTEXPR uint8_t varint_four_bytes = 0xfe;
BC_CONSTEXPR uint8_t varint_eight_bytes = 0xff;

// String padding sentinel.
BC_CONSTEXPR uint8_t string_terminator = 0x00;

// Witness serialization values (bip141).
//-----------------------------------------------------------------------------

BC_CONSTEXPR uint8_t witness_marker = 0x00;
BC_CONSTEXPR uint8_t witness_flag = 0x01;
BC_CONSTEXPR uint32_t witness_head = 0xaa21a9ed;
BC_CONSTEXPR size_t fast_sigops_factor = 4;
BC_CONSTEXPR size_t max_fast_sigops = fast_sigops_factor * max_block_sigops;
BC_CONSTEXPR size_t light_weight_factor = 4;
BC_CONSTEXPR size_t max_block_weight = light_weight_factor * max_block_size;
BC_CONSTEXPR size_t base_size_contribution = 3;
BC_CONSTEXPR size_t total_size_contribution = 1;
BC_CONSTEXPR size_t min_witness_program = 2;
BC_CONSTEXPR size_t max_witness_program = 40;

// Currency unit constants (uint64_t).
//-----------------------------------------------------------------------------

BC_CONSTFUNC uint64_t max_money_recursive(uint64_t money)
{
    return money > 0 ? money + max_money_recursive(money >> 1) : 0;
}

BC_CONSTEXPR uint64_t satoshi_per_bitcoin = 100000000;
BC_CONSTFUNC uint64_t bitcoin_to_satoshi(uint64_t bitcoin_uints=1)
{
    return bitcoin_uints * satoshi_per_bitcoin;
}

BC_CONSTEXPR uint64_t initial_block_subsidy_bitcoin = 50;
BC_CONSTFUNC uint64_t initial_block_subsidy_satoshi()
{
    return bitcoin_to_satoshi(initial_block_subsidy_bitcoin);
}

BC_CONSTEXPR uint64_t recursive_money = 9999999989u;
BC_CONSTEXPR uint64_t retarget_subsidy_interval = 210000;
BC_CONSTEXPR uint64_t no_retarget_subsidy_interval = 150;
BC_CONSTFUNC uint64_t subsidy_interval(bool retarget=true)
{
    return retarget ? retarget_subsidy_interval : no_retarget_subsidy_interval;
}

//*****************************************************************************
// CONSENSUS: This is the true maximum amount of money that can be created.
// The satoshi client uses a "sanity check" value that is effectively based on
// a round but incorrect value of recursive_money, which is higher than this
// true value. Despite comments to the contrary in the satoshi code, no value
// could be consensus critical unless it was *less* than the true value.
//*****************************************************************************
BC_CONSTFUNC uint64_t max_money(bool retarget=true)
{
    ////// Optimize out the derivation of recursive_money.
    ////BITCOIN_ASSERT(recursive_money == max_money_recursive(
    ////    initial_block_subsidy_satoshi()));

    return recursive_money * subsidy_interval(retarget);
}

} // namespace libbitcoin

#endif
