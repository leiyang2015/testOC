# ByteTrader iOS(SDK)
##设计思路 123456

Bytetrade iOS(SDK)不保存钱包用户的私钥，需要授权的操作通过回调先由钱包签名

## 接入方法 Demo参考
URL https://github.com/pengpeng/bytetrade-ios-sdk.git


### 该项目使用单例持有对外的API Methods

#### 用户名 如果用户没有注册，需要将该参数置为nil；否则，将传入用户名(用户注册成功后，会在SDK中缓存该参数)
@property (nonatomic, strong) NSString *userID;

#### 用户地址 注册时使用
@property (nonatomic, strong) NSString *userAddress; 

#### 提币地址  以太坊地址
@property (nonatomic, strong) NSString *withdrawAddres;


#### FunctionMethods 跳转到BTT SDK; 回调到接入的项目，SDK已在内部实现，不需要在项目中处理 
- (void)openBTTransation 

#### 取消签名/放弃当前交易 => 买 、卖
- (void)cancelSignForTransation;

#### Delegate Methods
 注册账户成功 回调
- (void)registerAccountSuccessful:(NSString *)userID

#### 交易签名 买、卖  ByteTrade私钥签名
- (bytetrade::transaction)signTransationData:(bytetrade::transaction)transationData;

#### 撤销订单签名   ByteTrade私钥签名
- (bytetrade::transaction)signCancelOrderData:(bytetrade::transaction)cancelOrderTransation;

#### 提币签名 第一次签名 ByteTrade私钥签名
- (bytetrade::transaction)withdrawOrderData:(bytetrade::transaction)withdrawTransation;

#### 提币签名 第二次签名 response: 以太坊私钥 
- (NSString *)withdrawSecondeSignByWeb3;

#### 充值 web3使用;  response: index0(NSString类型,以太坊地址) address ; index1(NSString类型,以太坊私钥) privateKey
- (NSArray *)depositeFunction;


#### 重新提交提币请求  response : privateKey(以太坊私钥)
- (NSString *)resubmitWithdrawPrivateKey;


#### 充值时 需要显示当前币的资产数量 ;;;; contractAddress :合约地址 ;;;; chainType : 链的类型
- (NSString *)depositeValueContractAddress:(NSString *)contractAddress chainType:(BTTChainType)chainType ;

## 项目运行环境
切换软件运行环境:  BTTEnvironmentTypeTest 测试环境;   BTTEnvironmentTypeDistribute 正式环境
+ (instancetype)shareInstanceWithEnvironmentType:(BTTEnvironmentType)environmentType;


### 测试账号
#### 账户说明 
Bytetrade测试链上的见证节点账户 
用户名 bytetraderTest
助记词 @[@"age",@"economy",@"trash",@"door",@"gas",@"fiction",@"donate",@"peace",@"margin",@"grow",@"emerge",@"elbow"]


### 测试用以太坊测试网络地址 （Rinkeby Test Network）
用户名  0x44c69ffbad79e842a470e4bd284b3d80e6facc20
私钥    0f3f574fa2e725d25e6c75f53e1c256abd08a062ddd9e474dab9ef2d615d42b6

### 项目依赖
依赖库 | 说明
------------- | -------------
'SocketRocket', '0.5.1'  |   Socket推送库
'AFNetworking'    |    网络库
'ReactiveObjC', '3.0.0'   |   数据信号库 
'Masonry',  '~> 1.1.0'    |     布局库
'GCDObjC', '~> 0.3.0'  |   封装GCD API
'MJExtension', '~> 3.0.13'    |    数据模型化解析库
'IQKeyboardManager', '6.1.0'     |    键盘库 可以通过点击其他view收起键盘，复杂界面布局使用
'SafeObject'    |     安全库，做了下数组越界等的处理
'DZNEmptyDataSet'    |    空占位图，Tableview CollectionView为空时，展示空占位图
'MJRefresh', '3.1.15.3'    |    下拉刷新
'SDWebImage', '~> 4.0'    |    WebImage 加载网络图片、gif图
'SDCycleScrollView', '~> 1.3' | banner图
'SVProgressHUD', '~> 2.2.5'    |    loadingView指示  
'UIAlertController+Blocks'    |    alertView展示
'secp256k1.swift',:modular_headers => true    |     web3依赖库,256k1加密算法
'Web3',:modular_headers => true    |    主要用来进行以太坊智能合约的提交。





