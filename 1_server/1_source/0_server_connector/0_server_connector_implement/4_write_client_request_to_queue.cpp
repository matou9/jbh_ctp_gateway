#include "../0_server_connector.h"
#include "string.h"

#include <iostream>
void server_connector::write_client_request_to_queue(int client_socket, char* p_message, int message_length)
{
    
    std::unique_lock<std::mutex> lock(client_request_queue_mutex);
    std::cout << "write client request thread" << std::this_thread::get_id() << " waiting..." << std::endl;
    client_request_queue_condition_variable.wait(lock, [this](){return client_request_queue.size() < client_request_queue_max_size;});
    
    message_block *request_message_block = new std::pair<char*, int>(p_message, message_length);
    client_message_block client_request_message_block = std::pair<int, message_block*>(client_socket, request_message_block);
    client_request_queue.push(client_request_message_block);
    lock.unlock();
    std::cout << "write client request thread" << std::this_thread::get_id() << " write client request to queue" << std::endl;
    client_request_queue_condition_variable.notify_all();
    
}