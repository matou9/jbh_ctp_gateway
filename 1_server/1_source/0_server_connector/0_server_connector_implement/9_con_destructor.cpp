#include "../0_server_connector.h"

#include <unistd.h>

server_connector::server_connector(std::string port, int max_client_number) : 
max_client_number(max_client_number), 
current_client_number(0),
server_socket(0),
server_address(),
accept_thread(nullptr),
stop_interact_threads(),
receive_client_message_threads(),
client_request_queue_mutex(),
client_request_queue_condition_variable(),
client_request_queue_max_size(100),
client_request_queue(),
process_client_request_thread(nullptr),
server_response_queue_mutex(),
server_response_queue_condition_variable(),
server_response_queue_max_size(100),
server_response_queue(),
process_server_response_thread(nullptr),
p_trade_gateway(nullptr)
{
    init(port);
    for (int i = 0; i < max_client_number; i++)
    {
        receive_client_message_threads[i] = nullptr;
        stop_interact_threads[i].store(false);
    }
}

server_connector::~server_connector()
{
    for (auto iter = receive_client_message_threads.begin(); iter != receive_client_message_threads.end(); iter++)
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

    if (process_server_response_thread != nullptr)
    {
        process_server_response_thread->join();
        delete process_server_response_thread;
    }

    // if (p_trade_gateway != nullptr)
    // {
    //     delete p_trade_gateway;
    // }
    
    while (!client_request_queue.empty())
    {
        message_block *message = client_request_queue.front().second;
        if (message->first != nullptr)
        {
            delete [] message->first;
        }
        delete message;
        client_request_queue.pop();
    }

    while (!server_response_queue.empty())
    {
        message_block *message = server_response_queue.front().second;
        if (message->first != nullptr)
        {
            delete [] message->first;
        }
        delete message;
        server_response_queue.pop();
    }


    close(server_socket);
}