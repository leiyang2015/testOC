#pragma once
#include "operation.h"
//#include "secp256k1.h"
//#include "ec_public.hpp"

namespace bytetrade {
    
    struct transaction {
        
        /* Default expiration time */
        //static int DEFAULT_EXPIRATION_TIME = 30;
        
        bytes chainId;
        // private ECKey privateKey;
        
        time_spec timestamp;
        optional<time_spec> expiration;
        vector<base_operation*> operations;
        uint8_t validate_type;
        optional<account_id_type> dapp;
        optional<ripemd160> proposal_transaction_id;
        bytes signature;
        
        transaction() {
            chainId = fromUserHex("0000000000000000000000000000000000000000000000000000000000000001");
            operations.clear();
        }
        
        transaction(vector<base_operation*> operationList) {
            chainId = fromUserHex("0000000000000000000000000000000000000000000000000000000000000001");
            
            operations = operationList;
        }
        
        vector<base_operation*> getOperations() { return operations; }
        
        bytes toBytes(bool containChainid);
        
        void sign(libbitcoin::ec_secret secret);
        
        string transaction_id();
        jsonxx::Object toJsonObject();
        
    };
    
}

