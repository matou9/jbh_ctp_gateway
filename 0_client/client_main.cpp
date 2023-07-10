#include "0_include/1_future_api.h"
#include <unistd.h>
#include <string.h>
#include <string>

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



    return 0;

}