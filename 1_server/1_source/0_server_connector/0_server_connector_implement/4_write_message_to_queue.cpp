#include "../0_server_connector.h"
#include "string.h"

#include <iostream>
void server_connector::write_message_to_queue(char* p_message, int message_length)
{
    
    std::unique_lock<std::mutex> lock(client_request_queue_mutex);
    std::cout << "write thread" << std::this_thread::get_id() << " waiting..." << std::endl;
    client_request_queue_condition_variable.wait(lock, [this](){return client_request_queue.size() < client_request_queue_max_size;});
    
    std::pair<char*, int> *message_block = new std::pair<char*, int>(p_message, message_length);
    client_request_queue.push(message_block);
    lock.unlock();
    std::cout << "write thread" << std::this_thread::get_id() << " write message to queue" << std::endl;
    client_request_queue_condition_variable.notify_all();
    
}