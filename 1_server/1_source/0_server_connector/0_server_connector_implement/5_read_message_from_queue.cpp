#include "../0_server_connector.h"
#include <iostream>
void server_connector::read_message_from_queue()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(client_request_queue_mutex);
        std::cout << "read thread" << std::this_thread::get_id() << " waiting..." << std::endl;
        client_request_queue_condition_variable.wait(lock, [this](){return client_request_queue.size() > 0;});
        std::pair<char*, int>* message_block = client_request_queue.front();
        client_request_queue.pop();
        lock.unlock();
        std::cout << "read thread" << std::this_thread::get_id() << " read message from queue " << std::endl;    
        client_request_queue_condition_variable.notify_all();

        process_client_request(message_block->first, message_block->second);
        delete [] message_block->first;
        delete message_block;
    }
    
}