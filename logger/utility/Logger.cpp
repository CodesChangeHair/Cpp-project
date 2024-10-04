#include "Logger.h"
#include <time.h>
#include <stdexcept>    // logic_error()
#include <string.h>     // strerror()
#include <iostream>
#include <stdarg.h>     // vsnprintf()
using namespace whao::utility;

const char *Logger::s_level[LEVEL_COUNT] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

Logger* Logger::m_instance = NULL;

Logger::Logger() : m_level(DEBUG), m_max(0), m_len(0)
{
}

Logger::~Logger()
{
    close();
}

Logger* Logger::instance()
{
    if (!m_instance)
        m_instance = new Logger();
    return m_instance;
}

void Logger::open(const string &filename)
{
    m_filename = filename;
    m_fout.open(filename, ios::app);
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed" + filename);
    }
    // file current size
    m_fout.seekp(0, ios::end);
    m_len = m_fout.tellp();
}

void Logger::close()
{
    m_fout.close();
}

void Logger::log(Level level, const char *file, int line, const char *format, ...)
{
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed" + m_filename);
    }
    
    if (m_level > level)
        return;

    time_t ticks = time(NULL);
    struct tm *ptm = localtime(&ticks);
    // 32 % 4 = 0 alignment 
    char timestamp[32] = {0};
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ptm);

    // save file format
    const char *fmt = "%s %s %s:%d "; 
    int size = snprintf(NULL, 0, fmt, timestamp, s_level[level], file, line);
    if (size > 0) 
    {
        char *buffer = new char[size + 1];
        snprintf(buffer, size + 1, fmt, timestamp, s_level[level], file, line);
        buffer[size + 1] = '\0';
        m_fout << buffer;
        m_len += size;
        delete buffer;
    }
    
    va_list arg_ptr;  
    va_start(arg_ptr, format);
    size = vsnprintf(NULL, 0, format, arg_ptr);
    if (size > 0)
    {
        char *buffer = new char[size + 1];
        va_start(arg_ptr, format);
        vsnprintf(buffer, size + 1, format, arg_ptr);
        m_fout << buffer;
        m_len += size;
        delete buffer;
    }
    va_end(arg_ptr);
    m_fout << "\n";
    m_fout.flush();

    if (m_max > 0  && m_len >= m_max) {
        rotate();        
    }
}

void Logger::rotate()
{
    close();
    time_t ticks = time(NULL);
    struct tm *ptm = localtime(&ticks);
    char timestamp[32] = {0};
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ptm);
    string filename = m_filename + timestamp;
    if (rename(m_filename.c_str(), filename.c_str()) != 0)
    {
        throw std::logic_error("rename log file failed" + string(strerror(errno)));
    }
    open(m_filename);
}
