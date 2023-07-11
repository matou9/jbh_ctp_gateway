#include "../0_server_connector.h"

void server_connector::accept_clients()
{
    while (current_client_number.load() < max_client_number)
    {
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t client_address_size;
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
        if(client_socket==-1)
        {
            error_handling("accept() error");
        }
        else
        {
            current_client_number.fetch_add(1);
            printf("Connected 1 new client, current client num: %d\n", current_client_number.load());
        }
        
        if (current_client_number.load() == max_client_number)
        {
            printf("Max client num reached, stop accepting new clients\n");
        }
        receive_client_message_threads[client_socket] = new std::thread(&server_connector::receive_client_request, this, client_socket);
    }
}