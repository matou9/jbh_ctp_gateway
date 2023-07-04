#include "1_source/1_client_connector/0_client_connector.h"
#include "0_include/1_future_api.h"
#include <unistd.h>
#include <string.h>


int main()
{
    client_connector *p_client = new client_connector("192.168.187.136", "1234");
    p_client->start_receive();

    //用户输入
    future_limit_entrust entrust;
    strcpy(entrust.exchange_code, "SHFE");
    strcpy(entrust.instrument_code, "rb2001");
    entrust.direction = E_LONG;
    entrust.offset = E_OPEN;
    entrust.limit_price = 1000;
    entrust.volume = 1;
    memset(entrust.entrust_id, 0, sizeof(entrust.entrust_id));
    strcpy(entrust.executor, "test");

    //test客户端底层发送
    char buf[BUF_SIZE];
    memcpy(buf, &entrust, sizeof(future_limit_entrust));
    p_client->send_to_server(buf, sizeof(future_limit_entrust));

    sleep(1);// 等待接收线程接收到消息

    
    p_client->stop_receive();
    delete p_client;
    return 0;

}