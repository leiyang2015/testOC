//
//  BTAccountSecp256.hpp
//  BTTrader
//
//  Created by 杨杨 on 2018/8/8.
//  Copyright © 2018年 yanglei. All rights reserved.
//

#ifndef BTAccountSecp256_hpp
#define BTAccountSecp256_hpp

#include <stdio.h>
#include "transaction.h"
#include <iostream>
#include "account.h"
#include "address.h"
#include "base_operation.h"

/////!<通过用户名 & 助记词 获取账号
std::string newAccountData(std::string userID, std::string memString);

/////!<通过助记词 获取公钥
std::string publicKeyFromMnemonicString(std::string mnemonicString);

/////!<通过助记词获取地址
std::string addressFromMnemonicString(std::string mnemonicString);

/////!<获取私钥
libbitcoin::ec_secret privateKeyFromMnemonicString(std::string mnemonicString);

////!<取消订单transaction
//bytetrade::order_cancel cancelOrder

#endif /* BTAccountSecp256_hpp */
