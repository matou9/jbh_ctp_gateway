#include "../0_server_connector.h"

void server_connector::run_server()
{
    accept_thread = new std::thread(&server_connector::accept_clients, this);
    accept_thread->join();
}