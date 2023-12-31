#include "../0_server_connector.h"

void server_connector::run_server()
{
    accept_thread = new std::thread(&server_connector::accept_clients, this);
    process_client_request_thread = new std::thread(&server_connector::read_client_request_from_queue, this);
    //debug
    process_server_response_thread = new std::thread(&server_connector::read_server_response_from_queue, this);
    
    accept_thread->join();
    process_client_request_thread->join();
    process_server_response_thread->join();
    
}