#include "../0_client_connector.h"
#include "0_include/1_future_api.h"

// void write_to_file(char* message, int message_length);
void client_connector::receive_from_server()
{
    while(true) 
    {
        char message[BUF_SIZE];
        int message_length;
        message_length = read(sock, message, BUF_SIZE-1);              //接收来自服务器端的消息
        if (message_length == -1)
        {
            printf("server disconnected\n");
            break;
        }
        if (message_length == 1 && message[0] == -1)
        {
            printf("server accepted disconnect request\n");
            break;
        }
        message[message_length]= '\0';                               //在字符数组尾部添加字符串结束符'\0'
        printf("Message from server: %s\n", message);           //输出接收到的消息字符串

        //TODO
        //一个成员变量, 取走这个消息, 执行事件回调
        //此处实现写入文件
        // write_to_file(message, message_length);

    
    }
    printf("stop receive thread\n");                           //输出停止接收消息线程的消息
}

// void write_to_file(char* message, int message_length)
// {
//         char *p_message = message;
//         callback_type type = (callback_type)(p_message[0]);
//         if (type == E_ON_CONNECTED)
//         {
//             printf("connected\n");
//         }
//         else if (type == E_ON_DISCONNECTED)
//         {
//             printf("disconnected\n");
//         }
//         else if (type == E_ON_ORDER_STATUS_UPDATE)
//         {
//             p_message += sizeof(callback_type);
//             FILE* fp = fopen("order_status_update.txt", "a");
//             fwrite(p_message, 1, message_length - sizeof(callback_type), fp);
//         }
//         else if (type == E_ON_TRADE_UPDATE)
//         {
//             p_message += sizeof(callback_type);
//             FILE* fp = fopen("trade_update.txt", "a");
//             fwrite(p_message, 1, message_length - sizeof(callback_type), fp);
//         }
//         else
//         {
//             printf("unknown message type\n");
//         }

// }