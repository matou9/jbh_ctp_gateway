#include "../0_client_connector.h"

client_connector::client_connector(std::string ip, std::string port) : stop_receive_thread(false), receive_thread(nullptr)
{
    init(ip, port);
    connect_to_server();
}

client_connector::~client_connector()
{
    if (stop_receive_thread.load() == false) 
    {
        stop_receive_thread.exchange(true); // 设置停止接收标志
    }
    if (receive_thread != nullptr) 
    { // 等待接收线程结束
        receive_thread->join();
        delete receive_thread; // 释放线程对象的内存
    }
    close(sock);
}