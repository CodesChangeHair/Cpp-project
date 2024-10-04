#include <iostream>
using namespace std;

 #include "utility/Logger.h"
using namespace whao::utility;

int main()
{
    Logger::instance()->open("./test.log");
    Logger::instance()->set_max_filesize(1024);
    debug("hello world file size is getting logger");
    info("info msg logger...");
    warn("warn msg logger...");
    error("error msg logger...");
    fatal("fatal msg loger...");
    return 0;
}
