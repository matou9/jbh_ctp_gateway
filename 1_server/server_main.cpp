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
    gateway->prepare("../CTPConnect.json");

    sleep(3);//TODO 通知机制

    std::string port = "1234";
    server_connector *server = new server_connector(port, 10);
    server->add_gateway(gateway);

    server->run_server();

    
    
    gateway->join();
    return 0;

}