#include "../0_CTP_gateway.h"
#include "0_server_connector/0_server_connector.h"

#include <iostream>
#include "string.h"
#define MEM_PADDING_SIZE 8
void CTP_offset_to_future_offset(const TThostFtdcOffsetFlagType &CTP_offset, future_offset_type &offset);
void CTP_gateway::OnRtnTrade(CThostFtdcTradeField * pTrade)
{
    std::cout << "CTP_gateway::OnRtnTrade(): 成交回报, OrderSysID: " << pTrade->OrderSysID << std::endl;
    //成交信息读取
    uint32_t trade_date = strtoul(pTrade->TradeDate, nullptr, 10);
    uint64_t trade_time = strtoul(pTrade->TradeTime, nullptr, 10);
    double trade_price = pTrade->Price;
    uint32_t trade_volume = pTrade->Volume;
    future_direction_type direction;
    if (pTrade->Direction == THOST_FTDC_D_Buy)
    {
        direction = E_LONG;
    }
    else if (pTrade->Direction == THOST_FTDC_D_Sell)
    {
        direction = E_SHORT;
    }
    future_offset_type offset;
    CTP_offset_to_future_offset(pTrade->OffsetFlag, offset);
    //读取order_id
    char order_id[64];
    sprintf(order_id, "#%s#%s", pTrade->ExchangeID, pTrade->OrderSysID);
    //读取trade_id
    char trade_id[64];
    sprintf(trade_id, "#%s#%s#%c", pTrade->ExchangeID, pTrade->TradeID, pTrade->Direction);
    //创建buf回报成交信息
    callback_type type = E_ON_TRADE_UPDATE;
    int buf_size = sizeof(future_limit_trade) + MEM_PADDING_SIZE;
    char* buf = new char[buf_size];
    memset(buf, 0, buf_size);
    char* ptr = buf;
    ptr[0] = type;
    ptr += MEM_PADDING_SIZE;
    //从order_map中找到对应的order
    if (order_map.find(order_id) == order_map.end())
    {
        std::cout << "CTP_gateway::OnRtnTrade(): 未找到对应的order, 什么情况? OrderSysID: " << pTrade->OrderSysID << std::endl;
        return;
    }
    else
    {
        client_order* p_order_pair = order_map[order_id];
        future_limit_order* this_order = p_order_pair->second;
        future_limit_trade* this_trade = new future_limit_trade();
        memset(this_trade, 0, sizeof(future_limit_trade));
        memcpy(&this_trade->origin_order, this_order, sizeof(future_limit_order));
        this_trade->trade_date = trade_date;
        this_trade->trade_time = trade_time;
        this_trade->trade_price = trade_price;
        this_trade->trade_volume = trade_volume;
        this_trade->direction = direction;
        this_trade->offset = offset;
        memcpy(this_trade->trade_id, trade_id, sizeof(trade_id));
        //成交不需要在本地维护了
        memcpy(ptr, this_trade, sizeof(future_limit_trade));
        //回报给客户端
        if (server_api != nullptr)
        {
            server_api->write_server_response_to_queue(p_order_pair->first, buf, buf_size);
        }
        else
        {
            //TODO CTP交易网关独立运行
        }

    }

}

void CTP_offset_to_future_offset(const TThostFtdcOffsetFlagType &CTP_offset, future_offset_type &offset)
{
    if (CTP_offset == THOST_FTDC_OF_Open)
    {
        offset = E_OPEN;
    }
    else if (CTP_offset == THOST_FTDC_OF_Close)
    {
        offset = E_CLOSE;
    }
    else if (CTP_offset == THOST_FTDC_OF_CloseToday)
    {
        offset = E_CLOSE_TODAY;
    }
    else if (CTP_offset == THOST_FTDC_OF_CloseYesterday)
    {
        offset = E_CLOSE_YESTERDAY;
    }
    else
    {
        std::cout << "CTP_gateway::CTP_offset_to_future_offset(): 未知的开平类型" << std::endl;
    }
}