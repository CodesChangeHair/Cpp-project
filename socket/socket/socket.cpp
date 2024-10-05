#include <socket/socket.h>
using namespace whao::socket;

Socket::Socket() : m_ip(""), m_port(0), m_sockfd(0) 
{
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sockfd < 0) 
    {
        log_error("create socket error");
    }
    log_debug("create socket success!");
}

Socket::Socket(int sockfd) : m_ip(""), m_port(0), m_sockfd(sockfd)
{

}

Socket::~Socket()
{
    close();
}

bool Socket::bind(const string &ip, int port)
{
    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    if (ip.empty())
    {
        // bind to any local ip address 
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    }
    sockaddr.sin_port = htons(port);
    if (::bind(m_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        log_error("sock bind error");
        return false;
    }
    log_debug("sock bind success!");
    m_ip = ip;
    m_port = port;
    return true;
}

bool Socket::listen(int backlog)
{
    if (::listen(m_sockfd, backlog) < 0)
    {
        log_error("socket listen error");
        return false;
    }
    log_debug("socket listening ...");
    return true;
}

bool Socket::connect(const string &ip, int port)
{
    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if (::connect(m_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        log_error("socket connect error");
        return false;
    }
    m_ip = ip;
    m_port = port;
    return true;
}

int Socket::accept()
{
    // connection (file?) descriptor
    int connfd = ::accept(m_sockfd, nullptr, nullptr);
    if (connfd < 0)
    {
        log_error("socket accept error");
        return -1;
    }
    log_debug("socket accept, connfd = %d", connfd);
    return connfd;
}

// return: size of send data
int Socket::send(const char *buf, int len)
{
    return ::send(m_sockfd, buf, len, 0);
}

int Socket::recv(char *buf, int len)
{
    return ::recv(m_sockfd, buf, len, 0);
}

void Socket::close()
{
    if (m_sockfd > 0)
    {
        ::close(m_sockfd);
        m_sockfd = 0;
    }
}
