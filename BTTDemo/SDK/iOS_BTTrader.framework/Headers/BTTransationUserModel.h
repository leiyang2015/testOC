//
//  BTTransationUserModel.h
//  BTTrader
//
//  Created by 杨杨 on 2018/9/3.
//  Copyright © 2018年 yanglei. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BTTransationUserDetailsModel;

@interface BTTransationUserModel : NSObject

@property (nonatomic, strong) NSArray<BTTransationUserDetailsModel *> *res;

@end

//account = "{\"id\":\"yanglei77777\",\"owner\":{\"weight_threshold\":100,\"account_auths\":[],\"key_auths\":[],\"address_auths\":[[\"BTTFdw83y8reAtgJcfo9QEMAq6fMuKLuQFbY\",100]]},\"active\":{\"weight_threshold\":100,\"account_auths\":[],\"key_auths\":[],\"address_auths\":[[\"BTTFdw83y8reAtgJcfo9QEMAq6fMuKLuQFbY\",100]]}}";
//address = BTTFdw83y8reAtgJcfo9QEMAq6fMuKLuQFbY;
//createtime = 1535961180;
//registrar = Aquila;
//userid = yanglei77777;
@interface BTTransationUserDetailsModel : NSObject

@property (nonatomic, strong) NSString *address;
@property (nonatomic, assign) long long createtime;
@property (nonatomic, strong) NSString *registrar;
@property (nonatomic, strong) NSString *userid;
@property (nonatomic, strong) NSString *account;

@end
