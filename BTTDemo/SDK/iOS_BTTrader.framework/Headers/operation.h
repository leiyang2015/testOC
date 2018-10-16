#ifndef __OPERATION_H__
#define __OPERATION_H__

#include "base.h"
#include "base_operation.h"
#include "op_wrapper.h"
#include "ripemd160.h"

namespace bytetrade {

struct order_cancel : base_operation {
  public:
    order_cancel() {
        type = order_cancel_operation;
    }
    uint128_t fee;

    ripemd160 order_id;
    string market_name;
    account_id_type creator;

    virtual jsonxx::Array toJsonObject();

    virtual bytes toBytes();
};

struct order_create : base_operation {
  public:
    order_create() {
        type = order_create_operation;
    }
    uint128_t fee;
    account_id_type creator;
    uint8_t side;
    uint8_t order_type;
    string market_name;
    uint128_t amount;
    uint128_t price;
    bool use_btt_as_fee;
    optional<uint128_t> freeze_btt_fee;
    time_spec now;
    time_spec expiration;

    virtual jsonxx::Array toJsonObject();

    virtual bytes toBytes();
};

struct transfer : base_operation {
  public:
    transfer() {
        type = transfer_operation;
    }

    uint128_t fee;
    account_id_type from;
    account_id_type to;
    uint32_t asset_type;
    uint128_t amount;

    virtual jsonxx::Array toJsonObject();

    virtual bytes toBytes();
};

struct withdraw : base_operation {
  public:
    withdraw() {
        type = withdraw_operation;
    }

    uint128_t fee;
    account_id_type from;
    string to_external_address;
    uint32_t asset_type;
    uint128_t amount;

    virtual jsonxx::Array toJsonObject();

    virtual bytes toBytes();
};

struct propose : base_operation {
  public:
    propose() {
        type = proposal_operation;
    }

    uint128_t fee;
    account_id_type proposaler;
    vector<op_wrapper> proposed_ops;
    time_spec expiration_time;

    virtual jsonxx::Array toJsonObject();

    virtual bytes toBytes();
};
}

#endif