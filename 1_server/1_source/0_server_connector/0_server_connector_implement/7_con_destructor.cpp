#include "0_server_connector.h"

#include <unistd.h>

server_connector::server_connector(std::string port, int max_client_num) : max_client_num(max_client_num)
{
    init(port);
    accept_thread = nullptr;
    for (int i = 0; i < max_client_num; i++)
    {
        interact_threads[i] = nullptr;
        stop_interact_threads[i].store(false);
    }
}

server_connector::~server_connector()
{
    for (auto iter = interact_threads.begin(); iter != interact_threads.end(); iter++)
    {
        if (iter->second != nullptr)
        {
            stop_interact_with_client(iter->first);
        }

    }
    delete accept_thread;
    close(serv_sock);
}