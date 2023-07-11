#include "../0_server_connector.h"
#include <iostream>
void server_connector::read_client_request_from_queue()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(client_request_queue_mutex);
        std::cout << "read client request thread" << std::this_thread::get_id() << " waiting..." << std::endl;
        client_request_queue_condition_variable.wait(lock, [this](){return client_request_queue.size() > 0;});
        
        client_message_block client_request_message_block = client_request_queue.front();
        int client_socket = client_request_message_block.first;
        message_block* request_message_block = client_request_message_block.second;
        client_request_queue.pop();
        lock.unlock();
        std::cout << "read client request thread" << std::this_thread::get_id() << " read client request from queue " << std::endl;    
        client_request_queue_condition_variable.notify_all();

        process_client_request(client_socket, request_message_block->first, request_message_block->second);
        delete [] request_message_block->first;
        delete request_message_block;
    }
    
}