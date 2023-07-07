/*
 * 0_CTP_gateway.h
 * CTP交易柜台网关类声明
 * created by 唐尚涛
 */

#ifndef CTP_GATEWAY_H_
#define CTP_GATEWAY_H_

#include "0_future_gateway.h"
#include "1_future_data_class/0_future_limit_entrust.h"
#include "1_future_data_class/1_future_limit_order.h"
#include "1_future_data_class/2_future_limit_order_action.h"
#include "1_future_data_class/3_future_limit_trade.h"
#include "../0_trading_platform_api/CTP6.3.15/ThostFtdcTraderApi.h"

#include <string>
#include <stdint.h>
#include <unordered_map>
#include <atomic>
class CTP_gateway : public CThostFtdcTraderSpi, public future_gateway
{
private:
    CThostFtdcTraderApi* CTP_trader_api;   //CTP交易柜台接口

    //CTP客户端所需信息
    std::string front_addr;                 //前置地址
    std::string broker;                     //经纪公司代码
    std::string user;                       //用户代码
    std::string password;                   //密码
    std::string app;                        //应用标识
    std::string auth_code;                  //认证码
    std::string flow_dir;                   //流文件目录
    std::atomic<uint32_t>    request_id;    //请求编号, 由客户端维护, 递增
    //
    uint32_t    trading_day;    //当前交易日


    //以下维护唯一的委托id
    uint32_t front_id;       //前置编号
    uint32_t session_id;     //会话编号
    std::atomic<uint32_t>    order_ref;      //报单引用(考虑到多个客户端线程会改变该值, 故使用原子变量)

    //如何在本地维护委托、订单、成交信息? 如何分发这些信息?

public:
    CTP_gateway();
    virtual ~CTP_gateway() override;
public:

    virtual void prepare() override;
    virtual void limit_entrust_insert(future_limit_entrust* entrust) override;
    virtual void limit_order_action(future_limit_order_action* order_action) override;
private:
    virtual void init(const char* config_file_name) override;
    virtual void release() override;
    virtual void connect() override;
    virtual void disconnect() override;
    virtual void login() override;
    virtual void logout() override;

private:
    /*
     * 直接调用CTP接口的函数
     */
    void req_connect();                     //请求连接
    void req_authenticate();                //请求认证
    void req_login();                       //请求登录
    void req_query_settlement_confirm();    //请求查询结算单确认情况
    void req_settlement_confirm();          //请求确认结算单
    void req_entrust_insert(future_limit_entrust* entrust);//请求报单
    void req_entrust_action(future_limit_order_action* action);//请求撤单

private:
    /*
     * 执行交易命令前的准备工作: 与柜台连接、登录、确认结算单信息
     */
    virtual void OnFrontConnected() override;
	virtual void OnFrontDisconnected(int nReason) override;
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    /*
     * CTP接受交易命令后的回报
     */
    virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) override;
    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) override;
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) override;

private:
    /*
     * 数据结构转换
     */

private:
    /*
     * 其他辅助函数
     */
    uint32_t generate_new_request_id();
    bool is_error_response(CThostFtdcRspInfoField* pRspInfo);

};













#endif