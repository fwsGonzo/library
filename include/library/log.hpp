#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <string>

/**
 * To open a logfile:
 * 	  library::logger.open("myproject.log");
 *
 * To disable console/stdout ouputput:
 * logger.setOutputConsole(false);
 *
 * To inform about initialization/progression:
 * logger << Log::INFO << "* Sound system initialized" << Log::ENDL;
 *
 * To log an error:
 * logger << Log::ERR << "MyClass::myFunction(): Something bad happened: " << error_number <<
 *Log::ENDL;
 *
 * WARNING:
 * Not using ENDL to finish a << stream will cause a mutex deadlock
 *
 **/

namespace library
{
class Log
{
public:
    enum LogLevel
    {
        ENDL,
        INFO,
        WARN,
        ERR
    };

    Log() = default;
    Log(std::string filename);
    ~Log();
    void open(std::string);

    void output_to_console(bool enabled) { this->outputConsole = enabled; }

private:
    bool autoLock;
    std::string log;
    std::ofstream file;

    bool outputConsole = true;

    friend Log& operator<<(Log& out, const LogLevel level);
	friend Log& operator<<(Log& out, const std::string& str);
	friend Log& operator<<(Log& out, const char* str);
    template <class T>
    friend Log& operator<<(Log& out, const T t);
};

inline Log& operator<<(Log& out, const std::string& str)
{
    out.log += str;
    return out;
}
inline Log& operator<<(Log& out, const char* str)
{
    out.log.append(str);
    return out;
}
template <class T>
inline Log& operator<<(Log& out, const T t)
{
    out.log += std::to_string(t);
    return out;
}

extern Log logger;

} // namespace library

#endif
