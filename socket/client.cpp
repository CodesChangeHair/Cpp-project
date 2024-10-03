#include <iostream>
#include <sys/socket.h>  // socket()
#include <netinet/in.h>  // IPPROTO_TCP
#include <arpa/inet.h>   // inet_addr()
#include <unistd.h>      // close()
#include <cstring>       // strerror()
#include <string>
using std::string;

#define error_msg(msg) printf("%s: errno = %d, errmsg = %s\n", msg, errno, strerror(errno))

int main()
{
    // 1. create socket
    int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        error_msg("create socket error");
        return 1;        
    }
    else
    {
        printf("create socket success!\n");
    }

    // 2. connect to server 
    string ip = "127.0.0.1";
    int port = 8080;

    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));  // init
    sockaddr.sin_family = AF_INET;
    // host address format to web format
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    // host to net (short) format
    sockaddr.sin_port = htons(port);

    if (::connect(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
    {
        error_msg("connect to server error");
        return 1;
    }
    else 
    {
        printf("client to server success!\n");
    }

    // 3. send request to server
    string data = "hello world";
    ::send(sockfd, data.c_str(), data.size(), 0);

    // 4. recieve data from server
    char buf[1024] = {0};
    ::recv(sockfd, buf, sizeof(buf), 0);
    printf("recv: %s\n", buf);

    // close socket (connection)
    ::close(sockfd);

    return 0;
}
