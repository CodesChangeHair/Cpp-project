#pragma once

#include <sys/socket.h>     // socket()
#include <netinet/in.h>     // IPPROTO_TCP
#include <arpa/inet.h>      // inet_addr()
#include <unistd.h>         // close()
#include <cstring>          // strerror()
#include <string>
using std::string;

#include <utility/logger.h>
using namespace whao::utility;

namespace whao{
namespace socket
{

#define log_debug(msg, ...)\
    debug(msg, ##__VA_ARGS__)

#define log_info(msg, ...)\
    info(msg, ##__VA_ARGS__)

#define log_error(msg)\
    error("%s: error = %d, errmsg = %s", msg, errno, strerror(errno))

#define log_warn(msg)\
    warn("%s: error = %d, errmsg = %s", msg, errno, strerror(errno))

#define log_fatal(msg)\
    fatal("%s: error = %d, errmsg = %s", msg, errno, strerror(errno))

class Socket
{
public:
    Socket();
    Socket(int sockfd);
    ~Socket();

    bool bind(const string &ip, int port);
    bool listen(int backlog);
    bool connect(const string &ip, int port);
    int accept();
    int send(const char *buf, int len);
    int recv(char *buf, int len);
    void close();

protected:
    string m_ip;
    int m_port;
    int m_sockfd;
};


}
}
