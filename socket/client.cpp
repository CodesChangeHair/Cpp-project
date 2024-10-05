#include <iostream>

#include <socket/socket.h>
using namespace whao::socket;

int main()
{
    // 1. create socket
    Socket client;

    // 2. connect to server 
    string ip = "127.0.0.1";
    int port = 8080;
    client.connect(ip, port);

    // 3. send request to server
    string data = "hello world";
    client.send(data.c_str(), data.size());

    // 4. recieve data from server
    char buf[1024] = {0};
    client.recv(buf, sizeof(buf));
    printf("recv: %s\n", buf);

    // close socket (connection)
    client.close();
}
