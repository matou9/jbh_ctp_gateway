#include "1_future_server/1_CTP_gateway/0_CTP_gateway.h"
#include "0_server_connector/0_server_connector.h"
#include <string.h>
#include <unistd.h>
int main(int argc, char** argv)
{
    // if (argc != 2)
    // {
    //     printf("input port\n");
    //     exit(1);
    // }
    // std::string port = argv[1];

    CTP_gateway *gateway = new CTP_gateway();
    std::string port = "1234";
    server_connector *server = new server_connector(port, 10);

    gateway->add_server(server);
    gateway->prepare("../CTPConnect.json");


    server->run_server();


    
    
    // gateway->join();
    return 0;

}