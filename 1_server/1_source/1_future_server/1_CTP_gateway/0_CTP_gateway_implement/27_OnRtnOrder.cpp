#include "../0_CTP_gateway.h"
#include "0_server_connector/0_server_connector.h"

#include <string.h>
#include <iostream>
void CTP_status_to_future_status(const TThostFtdcOrderStatusType &CTP_order_status, future_order_status_type &status);
#define MEM_PADDING_SIZE 8
void CTP_gateway::OnRtnOrder(CThostFtdcOrderField * pOrder)
{
    //读取entrust_id
    uint32_t this_order_ref = strtoul(pOrder->OrderRef, nullptr, 10);
    char this_entrust_id[64] = {0};
    sprintf(this_entrust_id, "#%d#%d#%d", front_id, session_id, this_order_ref);
    //读取order_id
    const char* exchange_id = pOrder->ExchangeID;
    const char* order_sys_id = pOrder->OrderSysID;//前面有空格?
    order_sys_id += 1;
    char this_order_id[64] = {0};
    sprintf(this_order_id, "#%s#%s", exchange_id, order_sys_id);
    //读取order信息
    uint32_t insert_date = strtoul(pOrder->InsertDate, nullptr, 10);
    uint64_t insert_time = strtoul(pOrder->InsertTime, nullptr, 10);                //TODO! 时间从 : :格式转化为整数
    uint32_t volume_left = pOrder->VolumeTotalOriginal - pOrder->VolumeTraded;
    future_order_status_type status;
    CTP_status_to_future_status(pOrder->OrderStatus, status);
    //从entrust_map中找到对应的委托
    client_entrust* p_entrust_pair = entrust_map[this_entrust_id];
    int this_client_socket = p_entrust_pair->first;
    future_limit_entrust *this_entrust = p_entrust_pair->second;

    //回报CTP接受到委托, 已发往交易所, 交易网关标记委托编号
    if (strlen(pOrder->OrderSysID) == 0)
    {
        std::cout << "CTP_gateway::OnRtnOrder(): CTP接受到委托, 已发往交易所" << std::endl;
        callback_type type = E_ON_ENTRUST_INSERTED;
        
        int buf_size = sizeof(future_limit_entrust) + MEM_PADDING_SIZE;
        char* buf = new char[buf_size];
        memset(buf, 0, buf_size);
        char* ptr = buf;
        ptr[0] = type;
        ptr += MEM_PADDING_SIZE;
        memcpy(ptr, this_entrust, sizeof(future_limit_entrust));
        //回报给客户端
        if (server_api != nullptr)
        {
            server_api->write_server_response_to_queue(this_client_socket, buf, sizeof(future_limit_entrust));
        }
        else
        {
            //TODO CTP交易网关独立运行
        }
    }
    //回报交易所已接受委托, 转换为订单; 或订单状态更新
    else
    {
        callback_type type = E_ON_ORDER_STATUS_UPDATE;
        int buf_size = sizeof(future_limit_order) + MEM_PADDING_SIZE;
        char* buf = new char[buf_size];
        memset(buf, 0, buf_size);
        char* ptr = buf;
        ptr[0] = type;
        ptr += MEM_PADDING_SIZE;

        //如果首次订单状态更新, 代表CTP将委托送到了交易所, 此时首次在本地维护订单
        if (order_map.find(this_order_id) == order_map.end())
        {
            std::cout << "CTP_gateway::OnRtnOrder(): 订单状态首次更新, OrderSysID: " << pOrder->OrderSysID << std::endl;
            future_limit_order* this_order = new future_limit_order();
            memset(this_order, 0, sizeof(future_limit_order));
            memcpy(&this_order->origin_entrust, this_entrust, sizeof(future_limit_entrust));
            this_order->insert_date = insert_date;
            this_order->insert_time = insert_time;
            memcpy(this_order->order_id, this_order_id, sizeof(this_order_id));
            this_order->volume_left = volume_left;
            this_order->status = status;
            client_order* p_order_pair = new client_order(this_client_socket, this_order);
            order_map[this_order_id] = p_order_pair;
            //回报给客户端
            memcpy(ptr, this_order, sizeof(future_limit_order));
            if (server_api != nullptr)
            {
                server_api->write_server_response_to_queue(this_client_socket, buf, buf_size);
            }
            else
            {
                //TODO CTP交易网关独立运行
            }
        }
        //如果并非首次订单状态更新, 则读取本地维护的订单, 更新订单状态
        else
        {
            std::cout << "CTP_gateway::OnRtnOrder(): 订单状态更新, OrderSysID: " << pOrder->OrderSysID << std::endl;
            client_order* p_order_pair = order_map[this_order_id];
            future_limit_order* this_order = p_order_pair->second;
            this_order->volume_left = volume_left;
            this_order->status = status;
            //回报给客户端
            memcpy(ptr, this_order, sizeof(future_limit_order));
            if (server_api != nullptr)
            {
                server_api->write_server_response_to_queue(this_client_socket, buf, sizeof(future_limit_order));
            }
            else
            {
                //TODO CTP交易网关独立运行
            }
        }

    }

}
void CTP_status_to_future_status(const TThostFtdcOrderStatusType &CTP_order_status, future_order_status_type &status)
{
    if (CTP_order_status == THOST_FTDC_OST_AllTraded)
    {
        status = E_ALL_TRADEED;
    }
    else if (CTP_order_status == THOST_FTDC_OST_PartTradedQueueing)
    {
        status = E_PART_TRADED_QUEUEING;
    }
    else if (CTP_order_status == THOST_FTDC_OST_PartTradedNotQueueing)
    {
        status = E_PART_TRADED_NOT_QUEUEING;
    }
    else if (CTP_order_status == THOST_FTDC_OST_NoTradeQueueing)
    {
        status = E_NO_TRADE_QUEUEING;
    }
    else if (CTP_order_status == THOST_FTDC_OST_NoTradeNotQueueing)
    {
        status = E_NO_TRADE_NOT_QUEUEING;
    }
    else if (CTP_order_status == THOST_FTDC_OST_Canceled)
    {
        status = E_CANCELED;
    }
}