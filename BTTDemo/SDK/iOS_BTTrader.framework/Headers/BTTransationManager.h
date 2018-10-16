//
//  BTTransationManager.h
//  BTTrader
//
//  Created by 杨杨 on 2018/8/24.
//  Copyright © 2018年 yanglei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "transaction.h"
#import "BTTransationUserModel.h"
#import "BTAccountSecp256Object.h"


typedef NS_ENUM(NSInteger,BTTChainType) {
    
    ////!<以太坊 或者 ERC20代币
    BTTChainTypeETH = 2,
    
    ////!<BTC代币
    BTTChainTypeBTC = 3
    
};

@protocol BTTransationDelegate <NSObject>

////!<注册账户成功
- (void)registerAccountSuccessful:(NSString *)userID;

////!<交易签名  ByteTrade私钥签名
- (bytetrade::transaction)signTransationData:(bytetrade::transaction)transationData;

////!<撤销订单签名  ByteTrade私钥签名
- (bytetrade::transaction)signCancelOrderData:(bytetrade::transaction)cancelOrderTransation;

//////!<提币签名 第一次签名 ByteTrade私钥签名
- (bytetrade::transaction)withdrawOrderData:(bytetrade::transaction)withdrawTransation;

/////!<提币签名 第二次签名 response: 以太坊私钥 
- (NSString *)withdrawSecondeSignByWeb3;

/////!<充值 web3使用;
/////!<response: index0(NSString类型,以太坊地址) address ; index1(NSString类型,以太坊私钥) privateKey
- (NSArray *)depositeFunction;

////!<重新提交提币请求 response : privateKey(以太坊私钥)
- (NSString *)resubmitWithdrawPrivateKey;

////!<充值时 需要显示当前币的资产数量 ;;;; contractAddress :合约地址 ;;;; chainType : 链的类型
- (NSString *)depositeValueContractAddress:(NSString *)contractAddress chainType:(BTTChainType)chainType;

@end


typedef NS_ENUM(NSInteger,BTTEnvironmentType) {
    
    ////!<测试环境
    BTTEnvironmentTypeTest = 0,
    ////!<正式环境
    BTTEnvironmentTypeDistribute = 1
};


@interface BTTransationManager : NSObject



+ (instancetype)shareInstanceWithEnvironmentType:(BTTEnvironmentType)environmentType;

@property (nonatomic, weak) id<BTTransationDelegate> BTTDelegate;

////!<用户名
@property (nonatomic, strong) NSString *userID;

////!<用户地址 注册时使用
@property (nonatomic, strong) NSString *userAddress;

////!<提币地址 以太坊地址
@property (nonatomic, strong) NSString *withdrawAddres;

/////!<获取运行环境
@property (nonatomic, assign, readonly) BTTEnvironmentType environmentType;

@property (nonatomic, strong) NSObject *web3TransationObj;

////!<跳转到BTT SDK
- (void)openBTTransation;

////!<取消签名/放弃当前交易 =>买 、卖
- (void)cancelSignForTransation;

////!<通过私钥生成地址
- (NSString *)getAddressByPrivateKey:(NSString *)privateKey;

////!<提币二次签名时 web3使用
//- (void)sendWithdrawPriviteKey:(NSString *)privateKey;

////!<根据地址查询用户 code 0 表示改地址下有用户 ; code -1表示该地址没有用户
- (void)requestUserAddress:(NSString *)userAddress callBackBlock:(void(^)(NSInteger code,BTTransationUserModel *userModelArray))callBackBlock;

////!<判断用户是否存在 code为0，表示这个ID可以被注册; code -1 表示该账户已被注册
- (void)requestUserID:(NSString *)userID callBackBlock:(void(^)(NSInteger code))callBackBlock;

////!<根据id查询用户
- (void)requestUserDataWithUserID:(NSString *)userID callBackBlock:(void(^)(NSInteger code,BTTransationUserModel *userModelArray))callBackBlock;



@end
