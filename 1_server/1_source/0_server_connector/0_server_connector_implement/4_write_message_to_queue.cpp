#include "../0_server_connector.h"
#include "string.h"
void server_connector::write_message_to_queue(char* message, int message_length)
{
    // std::lock_guard<std::mutex> lock(client_request_queue_mutex);
    // char* p_message = new char[message_length];
    // memcpy(p_message, message, message_length);
    // client_request_queue.push(p_message);
}