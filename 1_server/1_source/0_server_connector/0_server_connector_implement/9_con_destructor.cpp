#include "../0_server_connector.h"

#include <unistd.h>

server_connector::server_connector(std::string port, int max_client_number) : 
max_client_number(max_client_number), 
current_client_number(0),
client_request_queue_mutex(),
client_request_queue_max_size(100),
client_request_queue()
{
    init(port);
    accept_thread = nullptr;
    for (int i = 0; i < max_client_number; i++)
    {
        interact_threads[i] = nullptr;
        stop_interact_threads[i].store(false);
    }
    p_trade_gateway = nullptr;
    process_client_request_thread = nullptr;
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

    if (process_client_request_thread != nullptr)
    {
        process_client_request_thread->join();
        delete process_client_request_thread;
    }

    if (p_trade_gateway != nullptr)
    {
        delete p_trade_gateway;
    }
    
    close(server_socket);
}