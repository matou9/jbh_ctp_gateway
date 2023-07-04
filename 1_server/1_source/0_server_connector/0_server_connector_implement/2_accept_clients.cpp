#include "0_server_connector.h"

void server_connector::accept_clients()
{
    int accept_num = 0;
    while (accept_num++ < max_client_num)
    {
        int clnt_sock;
        struct sockaddr_in clnt_adr;
        socklen_t clnt_adr_sz;
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock==-1)
            error_handling("accept() error");
        else
            printf("Connected 1 new client, current client num: %d\n", accept_num);
        interact_threads[clnt_sock] = new std::thread(&server_connector::interact_with_one_client, this, clnt_sock);
        if (accept_num == max_client_num)
        {
            printf("Max client num reached, stop accepting new clients\n");

        }
    }
}