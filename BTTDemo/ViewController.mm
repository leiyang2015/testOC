//
//  ViewController.m
//  BTTrader2
//
//  Created by 杨杨 on 2018/8/29.
//  Copyright © 2018年 yanglei. All rights reserved.
//

#import "ViewController.h"

#import <iOS_BTTrader/BTTransationManager.h>

////!<以太坊钱包的私钥
#define  testPrivateKey  @"59ca857f5a88a93983aff526243bbc957766e384c87c6828c729594e81747a9a"

////!<以太坊钱包地址
#define testAddress  @"0xF167E4a540E0E84D867dD9DD6a7A8d3b4C0e32C9"

@interface ViewController ()<BTTransationDelegate>

@property (nonatomic, strong)BTTransationManager *manager;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self configueButton];
}


- (void)configueButton {

    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button setTitle:@"打开SDK" forState:UIControlStateNormal];
    [button setBackgroundColor:[UIColor cyanColor]];
    [button setFrame:CGRectMake(100, self.view.bounds.size.height/2 - 30, self.view.bounds.size.width-200, 60)];
    [button addTarget:self action:@selector(loginAccount) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];

}

- (BTTransationManager *)manager {
    if (!_manager) {
        _manager = [BTTransationManager shareInstanceWithEnvironmentType:BTTEnvironmentTypeDistribute];
    }
    return _manager;
}

//////!<用户注册
- (void)createUserAccount {

    self.manager.BTTDelegate = self;
    ////!<用户的userid
    self.manager.userID = nil;
    /////!<本地钱包 用户地址
    NSString *addressString = [BTAccountSecp256Object addressFromPrivateKey:testPrivateKey];

    __weak ViewController *weakSelf = self;
    [_manager requestUserAddress:addressString callBackBlock:^(NSInteger code, BTTransationUserModel *userModelArray) {

        if (userModelArray.res.count > 0) { ////!<该地址下有账户

        }else { /////!<该地址下没有账户
            weakSelf.manager.userAddress = addressString;
        }
    }];

    self.manager.withdrawAddres = testAddress;
    [self.manager openBTTransation];
}

////!<已有userid
- (void)loginAccount {

    self.manager.BTTDelegate = self;

    ////!<已注册成功的 userid
    NSString *userID = @"yanglei3456";
    /////!<已注册成功的 BTT用户地址  与 上述userid对应
    NSString *addressString = [BTAccountSecp256Object addressFromPrivateKey:testPrivateKey];

    self.manager.userID = userID;
    self.manager.userAddress = addressString;
    self.manager.withdrawAddres = testAddress;

    [self.manager openBTTransation];


    ////!<判断该userID是否已经注册成功
    __weak ViewController *weakSelf = self;
    [self.manager requestUserDataWithUserID:userID callBackBlock:^(NSInteger code, BTTransationUserModel *userModelArray) {

        if(userModelArray.res.count > 0) {
            for (BTTransationUserDetailsModel *model in userModelArray.res) {

                if([model.userid isEqualToString:userID] && [addressString isEqualToString:model.address]) {

                    weakSelf.manager.userID = userID;
                    weakSelf.manager.userAddress = addressString;

                    break;
                }
            }
        }
    }];
}


////!<注册账户成功
- (void)registerAccountSuccessful:(NSString *)userID {
    _manager.userID = userID;
}

////!<交易签名
- (bytetrade::transaction)signTransationData:(bytetrade::transaction)transationData {

    libbitcoin::ec_secret private_key = bytetrade::get_private_key([testPrivateKey UTF8String]);
    transationData.sign(private_key);

    return transationData;
}

////!<撤销订单
- (bytetrade::transaction)signCancelOrderData:(bytetrade::transaction)cancelOrderTransation {

    libbitcoin::ec_secret private_key = bytetrade::get_private_key([testPrivateKey UTF8String]);
    cancelOrderTransation.sign(private_key);

    return cancelOrderTransation;
}

//////!<提币签名 第一次签名  ByteTrade私钥签名
- (bytetrade::transaction)withdrawOrderData:(bytetrade::transaction)withdrawTransation {

    libbitcoin::ec_secret private_key = bytetrade::get_private_key([testPrivateKey UTF8String]);
    withdrawTransation.sign(private_key);

    return withdrawTransation;
}

/////!<提币签名 第二次签名 response: 以太坊私钥
- (NSString *)withdrawSecondeSignByWeb3 {
    return testPrivateKey;
}

////!<充值时 需要显示当前币的资产数量 ;;;; contractAddress :合约地址 ;;;; chainType : 链的类型
- (NSString *)depositeValueContractAddress:(NSString *)contractAddress chainType:(BTTChainType)chainType  {

    ////!<以太坊 或 ERC20代币
    if (chainType == BTTChainTypeETH) {
        return @"0.0055777";
    }else  { ////!< BTC等  预留
        return @"0.0055663";
    }
}


/////!<充值 web3使用; 返回值: index:0 address ; index:1 privateKey
- (NSArray *)depositeFunction {

    return @[testAddress,testPrivateKey];
}

////!<重新提币
- (NSString *)resubmitWithdrawPrivateKey {
    return  testPrivateKey;
}
@end
