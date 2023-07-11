#include "../0_server_connector.h"

#include <iostream>

void server_connector::write_server_response_to_queue(int client_socket, char* p_message, int message_length)
{
    
    std::unique_lock<std::mutex> lock(server_response_queue_mutex);
    std::cout << "write server response thread" << std::this_thread::get_id() << " waiting..." << std::endl;
    server_response_queue_condition_variable.wait(lock, [this](){return server_response_queue.size() < server_response_queue_max_size;});
    
    message_block *response_message_block = new std::pair<char*, int>(p_message, message_length);
    client_message_block server_response_message_block = std::pair<int, message_block*>(client_socket, response_message_block);
    server_response_queue.push(server_response_message_block);
    lock.unlock();
    std::cout << "write server response thread" << std::this_thread::get_id() << " write server response to queue" << std::endl;
    server_response_queue_condition_variable.notify_all();
    
}