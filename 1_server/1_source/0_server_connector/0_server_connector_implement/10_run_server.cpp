#include "../0_server_connector.h"

void server_connector::run_server()
{
    accept_thread = new std::thread(&server_connector::accept_clients, this);
    process_client_request_thread = new std::thread(&server_connector::read_message_from_queue, this);

    accept_thread->join();
    process_client_request_thread->join();
    
}