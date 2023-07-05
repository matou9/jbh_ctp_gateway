#include "0_include/1_future_api.h"
#include <unistd.h>
void future_api::init(std::string ip, std::string port)
{
    if (connector == nullptr)
    {
        connector = new client_connector(ip, port);
    }
    //此处阻塞等待连接成功, 可以采用异步回调的方式?
    while (!connector->is_connected)
    {
        sleep(1);
    }
    is_connected = true;
    connector->start_receive();

    
}