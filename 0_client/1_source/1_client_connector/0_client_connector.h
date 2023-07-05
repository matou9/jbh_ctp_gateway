/*
 * 0_client_connector.h
 * 客户端tcp连接类
 * created by 唐尚涛
 */

#ifndef CLIENT_CONNECTOR_H
#define CLIENT_CONNECTOR_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <thread>
#include <atomic>
#include <unistd.h>



#define BUF_SIZE 1024
class client_connector
{
private:
    int sock;
    struct sockaddr_in server_address;

    std::atomic<bool> stop_receive_thread;
    std::thread* receive_thread;
public:
    bool is_connected;
private:
    void error_handling(std::string message);
    void init(std::string ip, std::string port);
    void connect_to_server();
    void receive_from_server();
public:
    void start_receive();
    void send_to_server(char* message, int len);

    void stop_receive();

public:
    client_connector(std::string ip, std::string port);
    ~client_connector();

};











#endif