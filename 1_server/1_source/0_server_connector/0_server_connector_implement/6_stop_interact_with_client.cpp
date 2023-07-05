#include "../0_server_connector.h"

void server_connector::stop_interact_with_client(int client_socket)
{
    stop_interact_threads[client_socket].exchange(true);
    
}