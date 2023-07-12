#include "../0_server_connector.h"

#include <iostream>


void server_connector::read_server_response_from_queue()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(server_response_queue_mutex);
        std::cout << "server response thread" << std::this_thread::get_id() << " waiting..." << std::endl;
        server_response_queue_condition_variable.wait(lock, [this](){return server_response_queue.size() > 0;});
        
        client_message_block server_response_message_block = server_response_queue.front();
        int client_socket = server_response_message_block.first;
        message_block* response_message_block = server_response_message_block.second;
        
        server_response_queue.pop();
        lock.unlock();
        std::cout << "read server response thread" << std::this_thread::get_id() << " read server response from queue " << std::endl;    
        server_response_queue_condition_variable.notify_all();

        send_to_client(client_socket, response_message_block->first, response_message_block->second);

        delete [] response_message_block->first;
        delete response_message_block;
    }
    
}