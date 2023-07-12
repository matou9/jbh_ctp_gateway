/*
 * 0_server_connector.h
 * 交易服务端tcp连接类声明
 * created by 唐尚涛
 */
#ifndef SERVER_CONNECTOR_H
#define SERVER_CONNECTOR_H

// #include "1_source/1_future_server/1_CTP_gateway/0_CTP_gateway.h"

#include <arpa/inet.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <atomic>
#include <queue>
#include <mutex>
#include <utility>
#include <condition_variable>
#include <stdint.h>

typedef std::pair<char*, int> message_block;
typedef std::pair<int, message_block*> client_message_block;

class CTP_gateway;

#define BUF_SIZE 1024
class server_connector
{
private:
    int max_client_number;
    std::atomic<int> current_client_number;
    int server_socket;
    struct sockaddr_in server_address;
    
    std::thread* accept_thread;                                          //运行accept_clients函数, 接受客户端连接
    
    std::unordered_map<int, std::atomic<bool>> stop_interact_threads;

    std::unordered_map<int, std::thread*> receive_client_message_threads;       //对于每个客户端, 运行receive_client_message和write_client_message_to_queue函数, 
    
    std::mutex client_request_queue_mutex;                                      //接受客户端消息, 并将其写入客户端请求队列
    std::condition_variable client_request_queue_condition_variable;
    uint32_t client_request_queue_max_size;
    std::queue<client_message_block> client_request_queue;                      //客户端请求队列, 用于存储客户端请求, 以便于CTP网关处理
    
    std::thread* process_client_request_thread;                                 //运行read_client_message_from_queue函数和process_client_request函数, 
                                                                                //从客户端请求队列中取出客户端请求, 交给CTP网关处理
    

    std::mutex server_response_queue_mutex;
    std::condition_variable server_response_queue_condition_variable;
    uint32_t server_response_queue_max_size;
    std::queue<client_message_block> server_response_queue;                     //服务端响应队列, 用于存储CTP网关处理完客户端请求后的响应, 以便于服务端发送给客户端
    std::thread* process_server_response_thread;                                //运行read_message_from_queue函数和send_to_client函数, 
                                                                                //从服务端响应队列中取出服务端响应, 发送给客户端    
    CTP_gateway* p_trade_gateway;                                               //CTP网关指针, 用于处理客户端请求

private:
    void error_handling(std::string message);
    void init(std::string port);
    
    void accept_clients();
    
    void receive_client_request(int client_socket);                             //接受客户端消息
    void write_client_request_to_queue(int client_socket, char* message, int message_length);      //将客户端请求写入队列
    void read_client_request_from_queue();                                      //从队列中取出客户端请求
    void process_client_request(int client_socket, char* p_message, int message_length);           //交给CTPGateway处理
    
    friend CTP_gateway;
    void write_server_response_to_queue(int client_socket, char* message, int message_length);     //将服务端响应写入队列(提供给CTP网关)
    void read_server_response_from_queue();                                     //从队列中取出服务端响应
    void send_to_client(int client_socket, char* message, int message_length);  //发送服务端响应给客户端
    
    
    
    void stop_interact_with_client(int client_socket);
public:
    server_connector(std::string port, int max_client_number);
    ~server_connector();
    void run_server();
    void add_gateway(CTP_gateway* p_gateway);

};

#endif // SERVER_CONNECTOR_H