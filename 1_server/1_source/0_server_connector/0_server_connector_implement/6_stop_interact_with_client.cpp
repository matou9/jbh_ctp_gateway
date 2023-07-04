#include "0_server_connector.h"

void server_connector::stop_interact_with_client(int clnt_sock)
{
    stop_interact_threads[clnt_sock].exchange(true);
    
}