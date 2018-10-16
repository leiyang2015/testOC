//
//  BTAccountSecp256Object.h
//  BTTrader
//
//  Created by 杨杨 on 2018/8/8.
//  Copyright © 2018年 yanglei. All rights reserved.
//

#import <Foundation/Foundation.h>
@class BTAccountSecp256;


@interface BTAccountSecp256Object : NSObject

////!<通过 助记词 & userName =>  获取账户jsonString
+ (NSString *)createAccountByUserName:(NSString *)userName memArray:(NSArray *)array;

////!<SDK注册
+ (NSString *)SDKCreateAccountByUserName:(NSString *)userName;

///////!<通过助记词 获取公钥
+ (NSString *)publicKeyFromMnemonicArray:(NSArray *)array;

///////!<通过助记词获取地址
+ (NSString *)addressFromMnemonicArray:(NSArray *)array;

/////!<通过私钥 获取地址
+ (NSString *)addressFromPrivateKey:(NSString *)privateKey;

///////!<获取私钥
//+ (id)privateKeyFromMnemonicArray:(NSArray *)array;


@end
