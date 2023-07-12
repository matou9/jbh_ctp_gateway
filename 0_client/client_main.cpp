#include "0_include/1_future_api.h"
#include <unistd.h>
#include <string.h>
#include <string>

class test_spi : public future_spi
{
    virtual void on_entrust_inserted(future_limit_entrust *entrust) override
    {
        printf("test_spi::on_entrust_inserted\n");
        printf("entrust_id: %s\n", entrust->entrust_id);
    }
    virtual void on_order_status_update(future_limit_order *order) override
    {
        printf("test_spi::on_order_status_update\n");
        printf("order_id: %s\n", order->order_id);
    }
    virtual void on_trade_update(future_limit_trade *trade) override
    {
        printf("test_spi::on_trade_update\n");
        printf("trade_id: %s\n", trade->trade_id);
    }

};


int main(int argc, char** argv)
{
    // if (argc != 3)
    // {
    //     printf("input ip, port\n");
    //     exit(1);
    // }
    // std::string ip = argv[1];
    // std::string port = argv[2];
    std::string ip = "192.168.187.136";
    std::string port = "1234";
    future_api *api = new future_api();
    api->init(ip, port);
    api->register_spi(new test_spi());

    //用户输入
    future_limit_entrust entrust;
    strcpy(entrust.exchange_code, "SHFE");
    strcpy(entrust.instrument_code, "cu2307");
    entrust.direction = E_LONG;
    entrust.offset = E_OPEN;
    entrust.limit_price = 69000;
    entrust.volume = 2;
    memset(entrust.entrust_id, 0, sizeof(entrust.entrust_id));
    strcpy(entrust.executor, "test");

    // //test客户端底层发送
    api->limit_entrust_insert(&entrust);


    api->join();
    

    return 0;

}