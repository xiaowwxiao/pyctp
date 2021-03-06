#include "TdApi.h"

#include "ThostFtdcTraderApi.h"

#include "Windows.h"

TdApi::TdApi(){
    this->m_pThostFtdcTdApi = NULL;
    this->m_pTdSpi = NULL;
}

TdApi::TdApi(char *pszFlowPath){
    this->m_pThostFtdcTdApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);
    if (this->m_pThostFtdcTdApi == NULL){
        throw -1;
    }
}

///删除接口对象本身
///@remark 不再使用本接口对象时,调用该函数删除接口对象
void TdApi::Release(){
    this->m_pThostFtdcTdApi->Release();
}

///初始化
///@remark 初始化运行环境,只有调用后,接口才开始工作
void TdApi::Init(){
    this->m_pThostFtdcTdApi->Init();
}

///等待接口线程结束运行
///@return 线程退出代码
int TdApi::Join(){
    return this->m_pThostFtdcTdApi->Join();
}

///获取当前交易日
///@retrun 获取到的交易日
///@remark 只有登录成功后,才能得到正确的交易日
const char *TdApi::GetTradingDay(){
    return this->m_pThostFtdcTdApi->GetTradingDay();
}

///注册前置机网络地址
///@param pszFrontAddress：前置机网络地址。
///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
void TdApi::RegisterFront(char *pszFrontAddress){
    this->m_pThostFtdcTdApi->RegisterFront(pszFrontAddress);
}

///注册名字服务器网络地址
///@param pszNsAddress：名字服务器网络地址。
///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
///@remark RegisterNameServer优先于RegisterFront
void TdApi::RegisterNameServer(char *pszNsAddress){
    this->m_pThostFtdcTdApi->RegisterNameServer(pszNsAddress);
}

///注册名字服务器用户信息
///@param pFensUserInfo：用户信息。
void TdApi::RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo){
    this->m_pThostFtdcTdApi->RegisterFensUserInfo(pFensUserInfo);
}

///注册回调接口
///@param pSpi 派生自回调接口类的实例
void TdApi::RegisterSpi(){
    this->m_pTdSpi = new TdSpi(); ///派生自回调接口类的实例
    if (this->m_pTdSpi == NULL){
        throw -1;
    }

    this->m_pThostFtdcTdApi->RegisterSpi(this->m_pTdSpi);
}

///订阅私有流。
///@param nResumeType 私有流重传方式  
///        THOST_TERT_RESTART:从本交易日开始重传
///        THOST_TERT_RESUME:从上次收到的续传
///        THOST_TERT_QUICK:只传送登录后私有流的内容
///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
void TdApi::SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType){
    this->m_pThostFtdcTdApi->SubscribePrivateTopic(nResumeType);
}

///订阅公共流。
///@param nResumeType 公共流重传方式  
///        THOST_TERT_RESTART:从本交易日开始重传
///        THOST_TERT_RESUME:从上次收到的续传
///        THOST_TERT_QUICK:只传送登录后公共流的内容
///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
void TdApi::SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType){
    this->m_pThostFtdcTdApi->SubscribePublicTopic(nResumeType);
}

///客户端认证请求
int TdApi::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqAuthenticate(pReqAuthenticateField, nRequestID);
}

///用户登录请求
int TdApi::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqUserLogin(pReqUserLoginField, nRequestID);
}


///登出请求
int TdApi::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqUserLogout(pUserLogout, nRequestID);
}

///用户口令更新请求
int TdApi::ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
}

///资金账户口令更新请求
int TdApi::ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, nRequestID);
}

///报单录入请求
int TdApi::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqOrderInsert(pInputOrder, nRequestID);
}

///预埋单录入请求
int TdApi::ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqParkedOrderInsert(pParkedOrder, nRequestID);
}

///预埋撤单录入请求
int TdApi::ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
}

///报单操作请求
int TdApi::ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqOrderAction(pInputOrderAction, nRequestID);
}

///查询最大报单数量请求
int TdApi::ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQueryMaxOrderVolume(pQueryMaxOrderVolume, nRequestID);
}

///投资者结算结果确认
int TdApi::ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
}

///请求删除预埋单
int TdApi::ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
}

///请求删除预埋撤单
int TdApi::ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
}

///执行宣告录入请求
int TdApi::ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqExecOrderInsert(pInputExecOrder, nRequestID);
}

///执行宣告操作请求
int TdApi::ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqExecOrderAction(pInputExecOrderAction, nRequestID);
}

///询价录入请求
int TdApi::ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqForQuoteInsert(pInputForQuote, nRequestID);
}

///报价录入请求
int TdApi::ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQuoteInsert(pInputQuote, nRequestID);
}

///报价操作请求
int TdApi::ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQuoteAction(pInputQuoteAction, nRequestID);
}

///申请组合录入请求
int TdApi::ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqCombActionInsert(pInputCombAction, nRequestID);
}

///请求查询报单
int TdApi::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryOrder(pQryOrder, nRequestID);
}

///请求查询成交
int TdApi::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryTrade(pQryTrade, nRequestID);
}

///请求查询投资者持仓
int TdApi::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}

///请求查询资金账户
int TdApi::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID){
    OutputDebugString(pQryTradingAccount->BrokerID);
    OutputDebugString(pQryTradingAccount->InvestorID);
    OutputDebugString(pQryTradingAccount->CurrencyID);
    return this->m_pThostFtdcTdApi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
}

///请求查询投资者
int TdApi::ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInvestor(pQryInvestor, nRequestID);
}

///请求查询交易编码
int TdApi::ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryTradingCode(pQryTradingCode, nRequestID);
}

///请求查询合约保证金率
int TdApi::ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
}

///请求查询合约手续费率
int TdApi::ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
}

///请求查询交易所
int TdApi::ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryExchange(pQryExchange, nRequestID);
}

///请求查询产品
int TdApi::ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryProduct(pQryProduct, nRequestID);
}

///请求查询合约
int TdApi::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInstrument(pQryInstrument, nRequestID);
}

///请求查询行情
int TdApi::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
}

///请求查询投资者结算结果
int TdApi::ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
}

///请求查询转帐银行
int TdApi::ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryTransferBank(pQryTransferBank, nRequestID);
}

///请求查询投资者持仓明细
int TdApi::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
}

///请求查询客户通知
int TdApi::ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryNotice(pQryNotice, nRequestID);
}

///请求查询结算信息确认
int TdApi::ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}

///请求查询投资者持仓明细
int TdApi::ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
}

///请求查询保证金监管系统经纪公司资金账户密钥
int TdApi::ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, nRequestID);
}

///请求查询仓单折抵信息
int TdApi::ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryEWarrantOffset(pQryEWarrantOffset, nRequestID);
}

///请求查询投资者品种/跨品种保证金
int TdApi::ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, nRequestID);
}

///请求查询交易所保证金率
int TdApi::ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryExchangeMarginRate(pQryExchangeMarginRate, nRequestID);
}

///请求查询交易所调整保证金率
int TdApi::ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, nRequestID);
}

///请求查询汇率
int TdApi::ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryExchangeRate(pQryExchangeRate, nRequestID);
}

///请求查询二级代理操作员银期权限
int TdApi::ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, nRequestID);
}

///请求查询产品组
int TdApi::ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryProductGroup(pQryProductGroup, nRequestID);
}

///请求查询报单手续费
int TdApi::ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField *pQryInstrumentOrderCommRate, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, nRequestID);
}

///请求查询期权交易成本
int TdApi::ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, nRequestID);
}

///请求查询期权合约手续费
int TdApi::ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, nRequestID);
}

///请求查询执行宣告
int TdApi::ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryExecOrder(pQryExecOrder, nRequestID);
}

///请求查询询价
int TdApi::ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryForQuote(pQryForQuote, nRequestID);
}

///请求查询报价
int TdApi::ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryQuote(pQryQuote, nRequestID);
}

///请求查询组合合约安全系数
int TdApi::ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, nRequestID);
}

///请求查询申请组合
int TdApi::ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryCombAction(pQryCombAction, nRequestID);
}

///请求查询转帐流水
int TdApi::ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryTransferSerial(pQryTransferSerial, nRequestID);
}

///请求查询银期签约关系
int TdApi::ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryAccountregister(pQryAccountregister, nRequestID);
}

///请求查询签约银行
int TdApi::ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryContractBank(pQryContractBank, nRequestID);
}

///请求查询预埋单
int TdApi::ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
}

///请求查询预埋撤单
int TdApi::ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
}

///请求查询交易通知
int TdApi::ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
}

///请求查询经纪公司交易参数
int TdApi::ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryBrokerTradingParams(pQryBrokerTradingParams, nRequestID);
}

///请求查询经纪公司交易算法
int TdApi::ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, nRequestID);
}

///请求查询监控中心用户令牌
int TdApi::ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, nRequestID);
}

///期货发起银行资金转期货请求
int TdApi::ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqFromBankToFutureByFuture(pReqTransfer, nRequestID);
}

///期货发起期货资金转银行请求
int TdApi::ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqFromFutureToBankByFuture(pReqTransfer, nRequestID);
}

///期货发起查询银行余额请求
int TdApi::ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, int nRequestID){
    return this->m_pThostFtdcTdApi->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, nRequestID);
}

TdApi::~TdApi(){
    if (this->m_pThostFtdcTdApi)
    {
        this->m_pThostFtdcTdApi->RegisterSpi(NULL);
        this->m_pThostFtdcTdApi->Release();
        this->m_pThostFtdcTdApi = NULL;
    }

    if (this->m_pTdSpi)
    {
        delete this->m_pTdSpi;
        this->m_pTdSpi = NULL;
    }
}
