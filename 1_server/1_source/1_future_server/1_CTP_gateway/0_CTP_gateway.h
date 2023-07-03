/*
 * 0_CTP_gateway.h
 * CTP交易柜台网关类声明
 * created by 唐尚涛
 */

#ifndef CTP_GATEWAY_H_
#define CTP_GATEWAY_H_

#include "0_include/0_future_gateway.h"
#include "0_include/1_future_data_class/0_future_limit_entrust.h"
#include "0_include/1_future_data_class/2_future_limit_order_action.h"
#include "../0_trading_platform_api/CTP6.3.15/ThostFtdcTraderApi.h"

class CTP_gateway : public CThostFtdcTraderSpi, public future_gateway
{
private:
    CThostFtdcTraderApi* api;   //CTP交易柜台接口

public:
    CTP_gateway();
    virtual ~CTP_gateway() override;

    virtual void init() override;
    virtual void release() override;
    virtual void connect() override;
    virtual void disconnect() override;
    virtual void login() override;
    virtual void logout() override;
    virtual void confirm() override;

    virtual void entrust_insert(future_limit_entrust* entrust) override;
    virtual void entrust_action(future_limit_order_action* order_action) override;

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

};













#endif