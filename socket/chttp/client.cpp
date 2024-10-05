#include <iostream>
#include <sys/socket.h>  // 包含 socket() 函数相关定义
#include <netinet/in.h>  // 包含 IPPROTO_TCP 等协议相关定义
#include <arpa/inet.h>   // 包含 inet_addr() 函数，用于 IP 地址转换
#include <unistd.h>      // 包含 close() 函数，用于关闭文件描述符
#include <cstring>       // 包含 strerror() 函数，用于错误信息处理
#include <string>        // 用于 std::string 字符串类型
using std::string;

// 定义一个宏，用于打印错误信息，包含错误号和错误描述
#define error_msg(msg) printf("%s: errno = %d, errmsg = %s\n", msg, errno, strerror(errno))

int main()
{
    // 1. 创建客户端套接字
    // AF_INET: 使用 IPv4 协议
    // SOCK_STREAM: 使用 TCP 可靠流式传输
    // IPPROTO_TCP: 明确指定使用 TCP 协议
    int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        // 如果创建套接字失败，打印错误信息并退出程序
        error_msg("create socket error");
        return 1;
    }
    else
    {
        // 套接字创建成功，打印提示信息
        printf("create socket success!\n");
    }

    // 2. 连接到服务器
    string ip = "127.0.0.1";  // 服务器 IP 地址（这里为本地主机）
    int port = 8080;          // 服务器端口号

    struct sockaddr_in sockaddr;  // 用于存储服务器地址信息的结构体
    std::memset(&sockaddr, 0, sizeof(sockaddr));  // 初始化结构体为0
    sockaddr.sin_family = AF_INET;                // 设置地址族为 IPv4
    // inet_addr(): 将点分十进制的IP地址转换为网络字节序的二进制形式
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    // htons(): 将主机字节序的端口号转换为网络字节序
    sockaddr.sin_port = htons(port);

    // 使用 connect() 函数尝试连接到服务器
    if (::connect(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
    {
        // 如果连接失败，打印错误信息并退出程序
        error_msg("connect to server error");
        return 1;
    }
    else
    {
        // 连接成功，打印提示信息
        printf("client to server success!\n");
    }

    // 3. 发送数据到服务器
    string data = "hello world";  // 要发送的数据
    // 使用 send() 函数将数据发送到服务器
    // 参数分别是：套接字描述符、数据、数据长度、发送标志
    ::send(sockfd, data.c_str(), data.size(), 0);

    // 4. 接收来自服务器的回显数据
    char buf[1024] = {0};  // 定义缓冲区，用于接收服务器返回的数据
    // 使用 recv() 函数接收数据，存储在 buf 中
    ::recv(sockfd, buf, sizeof(buf), 0);
    // 打印接收到的数据
    printf("recv: %s\n", buf);

    // 关闭套接字，结束与服务器的连接
    ::close(sockfd);

    return 0;
}

