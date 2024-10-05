#include <iostream>

#include <socket/socket.h>
using namespace whao::socket;

int main()
{
    Logger::instance()->open("server.log");
    // 1. create socket
    Socket server;


    // 2. bind socket
    string ip = "127.0.0.1";
    int port = 8080;
    server.bind(ip, port);
    
    // listen to socket
    server.listen(1024);

    // wait for request
    while (true)
    {
        // 4. accept for client connection
        int connfd = server.accept();
        if (connfd < 0)
            return 1;

        Socket client(connfd);

        char buf[1024] = {0};

        // 5. accept for client data
        // len: client data length
        size_t len = client.recv(buf, sizeof(buf));
        printf("recv: connfd = %d, msg = %s\n", connfd, buf);

        // 6. send data to client
        client.send(buf, len);  // send client data back to client
    }

    // 7. close socket
    server.close();
    return 0;
}
