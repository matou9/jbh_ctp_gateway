#include "../0_server_connector.h"
#include <unistd.h>
void server_connector::stop_interact_with_client(int client_socket)
{
    stop_interact_threads[client_socket].exchange(true);
    receive_client_message_threads[client_socket]->join();
    delete receive_client_message_threads[client_socket];
    receive_client_message_threads[client_socket] = nullptr;
    close(client_socket);
    
}