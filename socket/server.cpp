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
    // :: global scope
    int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        printf("create socket error: errno = %d, errmsg = %s\n", errno, strerror(errno));
        return 1;
    }
    else
    {
        printf("create socket success!\n");
    }
    
    // avoid TIME_WAIT 
    int on = 1;
    int s = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (s < 0)
    {
        error_msg("setsockopt error");
        return 1;
    }

    // 2. bind socket
    string ip = "127.0.0.1";
    int port = 8080;

    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));  // init
    sockaddr.sin_family = AF_INET;
    // inet_addr: host address --> web address (big or small endian)
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str()); 
    // htons: host to net short
    sockaddr.sin_port = htons(port);
    if (::bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        error_msg("sock bind error"); 
        return 1;
    }
    else 
    {
        printf("socket bind success, ip = %s, port = %d\n", ip.c_str(), port);
    }
    
    // listen to socket
    if (::listen(sockfd, 1024) < 0)
    {
        error_msg("socket listen error");
        return 1;
    }
    else 
    {
        printf("socket listening ...\n");
    }

    // wait for request
    while (true)
    {
        // 4. accept for client connection
        int connfd = ::accept(sockfd, nullptr, nullptr);
        if (connfd < 0)
        {
            error_msg("socket accept error");
            return 1;
        }
        
        char buf[1024] = {0};

        // 5. accept for client data
        // len: client data length
        size_t len = ::recv(connfd, buf, sizeof(buf), 0);
        printf("recv: connfd = %d, msg = %s\n", connfd, buf);

        // 6. send data to client
        ::send(connfd, buf, len, 0);  // send client data back to client
    }

    // 7. close socket
    ::close(sockfd);
    return 0;
}
