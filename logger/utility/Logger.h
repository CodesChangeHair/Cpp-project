#pragma once

#include <string>
#include <fstream>
using namespace std;

namespace whao {
namespace utility {

#define debug(format, ...) \
    Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define info(format, ...) \
    Logger::instance()->log(Logger::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define warn(format, ...) \
    Logger::instance()->log(Logger::WARN, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define error(format, ...) \
    Logger::instance()->log(Logger::ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define fatal(format, ...) \
    Logger::instance()->log(Logger::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

class Logger
{
public:
    // level of message in log system
    enum Level
    {
        DEBUG = 0,
        INFO,
        WARN, 
        ERROR,
        FATAL,
        LEVEL_COUNT
    };
    // open and close a file
    void open(const string&);
    void close();
    // log(): save log information into file
    // parameters: level of message, file name, line: line of code, format ...: content
    // ...:  variadic arguments, allow function to accept an indefinite number of arguments
    void log(Level level, const char *file, int line, const char *format, ...);
    
    void set_level(Level level)
    {
        m_level = level;
    }

    void set_max_filesize(int bytes)
    {
        m_max = bytes;
    }

    // return single instance of Logger()
    static Logger* instance();
 

/* single instance */
private:
    Logger();
    ~Logger();
    // rotate log file: create a new file to store log infomation
    void rotate();

private:
    string m_filename; 
    ofstream m_fout;    // file stream
    Level m_level;
    // the maximum size of log file
    // if current file size m_len > m_max, create a new log file
    int m_max, m_len;
    static const char *s_level[LEVEL_COUNT];  // string format of message level
    static Logger *m_instance;
};


}
}
