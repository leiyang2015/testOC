#ifndef __BASE_OPERATION_H__
#define __BASE_OPERATION_H__

#include "base.h"
#include "jsonxx.h"
#include "optional.h"
#include "time_spec.h"
namespace bytetrade {

enum operation_type {
    transfer_operation = 0,
    order_create_operation,
    order_cancel_operation,
    deposit_operation,
    withdraw_operation,
    create_asset_operation,
    create_market_operation,
    witness_create_operation,
    witness_update_operation,
    deal_operation,
    order_cancel_settlement_operation,
    witness_minning_rewards_operation,
    pledge_asset_operation,
    redeem_asset_operation,
    redeem_asset_settlement_operation,
    set_balance_operation,
    vote_operation,
    execute_operation,
    proposal_operation,
    withdraw_settlement_operation,
    super_deposit_operation,
    order_freeze_btt_fee_settlement_operation,
    account_create_operation,
    account_update_operation,
    account_reset_claim
};

struct base_operation {
  public:
    operation_type type;

    operation_type which() {
        return type;
    }

    bytes getId() {
        return uint8_to_bytes(type);
    }

    virtual jsonxx::Array toJsonObject() {
//        cout << "base" << endl;
        jsonxx::Array o;
        return o;
    }

    virtual bytes toBytes() = 0;
};
}

#endif
