/*
 * 0_server_connector.h
 * 交易服务端tcp连接类声明
 * created by 唐尚涛
 */


#include <arpa/inet.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <atomic>

#define BUF_SIZE 1024
class server_connector
{
private:
    int max_client_num;
    int serv_sock;
    struct sockaddr_in serv_adr;
    

    std::thread* accept_thread;
    std::unordered_map<int, std::thread*> interact_threads;
    std::unordered_map<int, std::atomic<bool>> stop_interact_threads;

private:
    void error_handling(std::string message);
    void init(std::string port);
    void accept_clients();
    void interact_with_one_client(int clnt_sock);
    void process_client_message(int clnt_sock, char* message, int str_len);
    void send_to_client(int clnt_sock, char* message, int str_len);
    void stop_interact_with_client(int clnt_sock);
public:
    server_connector(std::string port, int max_client_num);
    ~server_connector();
    void run_server();
    
};