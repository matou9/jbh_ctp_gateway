#include "../0_client_connector.h"

client_connector::client_connector(std::string ip, std::string port) : receive_thread(nullptr), is_connected(false)
{
    init(ip, port);
    connect_to_server();
}

client_connector::~client_connector()
{
    if (sock != -1) 
    { // 关闭套接字
        close_connection();
    }
}