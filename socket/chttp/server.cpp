#include <iostream>
#include <sys/socket.h>  // 包含 socket() 函数相关的定义
#include <netinet/in.h>  // 包含 IPPROTO_TCP 等协议相关的定义
#include <arpa/inet.h>   // 包含 inet_addr() 函数，用于IP地址转换
#include <unistd.h>      // 包含 close() 函数，用于关闭文件描述符
#include <cstring>       // 包含 strerror() 函数，用于获取错误信息
#include <string>
using std::string;

// 定义一个宏，用于打印错误信息，包含错误号和对应的错误描述
#define error_msg(msg) printf("%s: errno = %d, errmsg = %s\n", msg, errno, strerror(errno))

int main()
{
    // 1. 创建套接字
    // :: 表示全局作用域，确保调用的是全局的 socket 函数
    int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        // 如果套接字创建失败，打印错误信息并返回错误码
        printf("create socket error: errno = %d, errmsg = %s\n", errno, strerror(errno));
        return 1;
    }
    else
    {
        // 套接字创建成功，打印成功信息
        printf("create socket success!\n");
    }

    // 设置套接字选项，避免 TIME_WAIT 状态
    int on = 1;
    // SOL_SOCKET: 套接字级别的选项
    // SO_REUSEADDR: 允许重用本地地址
    int s = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (s < 0)
    {
        // 如果设置套接字选项失败，打印错误信息并返回错误码
        error_msg("setsockopt error");
        return 1;
    }

    // 2. 绑定套接字到指定的IP地址和端口
    string ip = "127.0.0.1";  // 本地回环地址
    int port = 8080;           // 监听端口号

    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));  // 初始化 sockaddr 结构体为0
    sockaddr.sin_family = AF_INET;                // 设置地址族为 IPv4
    // inet_addr: 将点分十进制的IP地址转换为网络字节序的二进制形式
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    // htons: 将主机字节序转换为网络字节序（大端）
    sockaddr.sin_port = htons(port);
    // 绑定套接字到指定的IP地址和端口
    if (::bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        // 如果绑定失败，打印错误信息并返回错误码
        error_msg("sock bind error");
        return 1;
    }
    else
    {
        // 绑定成功，打印绑定信息
        printf("socket bind success, ip = %s, port = %d\n", ip.c_str(), port);
    }

    // 3. 监听套接字，等待连接
    // 第二个参数是监听队列的长度，这里设置为1024
    if (::listen(sockfd, 1024) < 0)
    {
        // 如果监听失败，打印错误信息并返回错误码
        error_msg("socket listen error");
        return 1;
    }
    else
    {
        // 监听成功，打印监听信息
        printf("socket listening ...\n");
    }

    // 4. 等待客户端连接请求
    while (true)
    {
        // 接受客户端连接
        // 第一个参数是监听套接字，后两个参数用于获取客户端的地址信息，这里不需要所以传入nullptr
        int connfd = ::accept(sockfd, nullptr, nullptr);
        if (connfd < 0)
        {
            // 如果接受连接失败，打印错误信息并返回错误码
            error_msg("socket accept error");
            return 1;
        }

        char buf[1024] = {0};  // 定义一个缓冲区，用于存储接收到的数据

        // 5. 接收来自客户端的数据
        // recv 函数从连接套接字中接收数据，存储在 buf 中，最大接收 sizeof(buf) 字节
        size_t len = ::recv(connfd, buf, sizeof(buf), 0);
        printf("recv: connfd = %d, msg = %s\n", connfd, buf);

        // 6. 将接收到的数据发送回客户端，实现简单的回显功能
        ::send(connfd, buf, len, 0);  // 将数据发送回客户端
    }

    // 7. 关闭套接字
    ::close(sockfd);
    return 0;
}

